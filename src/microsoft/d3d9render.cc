/* -*- coding: utf-8; indent-tabs-mode: t; tab-width: 4; c-basic-offset: 4; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

/*
 * The HAL for Direct3D 9
 */

extern "C" {
#include "../opennovel.h"
#include "d3drender.h"
};

// Direct3D 9.0
#include <d3d9.h>

//
// パイプラインの種類
//
enum  {
	PIPELINE_NORMAL,
	PIPELINE_ADD,
	PIPELINE_DIM,
	PIPELINE_RULE,
	PIPELINE_MELT,
};

//
// 座標変換済み頂点の構造体
//  - 頂点シェーダを使わないため、変換済み座標を直接指定している
//
struct Vertex
{
	float x, y, z;	// (x, y, 0)
	float rhw;		// (1.0)
	DWORD color;	// (alpha, 1.0, 1.0, 1.0)
	float u1, v1;	// (u, v) of samplerColor
	float u2, v2;	// (u, v) of samplerRule
};

//
// Direct3Dオブジェクト
//
static LPDIRECT3D9 pD3D;
static LPDIRECT3DDEVICE9 pD3DDevice;
static IDirect3DPixelShader9 *pDimShader;
static IDirect3DPixelShader9 *pRuleShader;
static IDirect3DPixelShader9 *pMeltShader;
static D3DPRESENT_PARAMETERS d3dpp;

//
// レンダリング対象のウィンドウ
//
static HWND hMainWnd;

//
// オフセットとスケール
//
static float fDisplayOffsetX;
static float fDisplayOffsetY;
static float fScale;

//
// シェーダ
//

// Note:
//  - 頂点シェーダはなく、固定シェーダを使用している
//  - "normal"パイプラインはピクセルシェーダではなく固定シェーダで実行する
//  - "add"パイプラインはピクセルシェーダではなく固定シェーダで実行する
//  - D3D9Xのランタイムを不要とするため、シェーダのコンパイルはオフラインで行ってある

//
// "dim"パイプラインのピクセルシェーダ
//
// dimShaderSrc[] =
//	"ps_1_4                                                    \n"
//	"                     // c0: the slot for dim factor       \n"
//	"texld r0, t0         // r0 = samplerColor;                \n"
//	"mul r0, r0, c0       // r0 *= c0;                         \n";
//                        // return r0;
//
static  unsigned char dimShaderBin[] {
	0x04, 0x01, 0xff, 0xff, 0x42, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0xb0,
	0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80,
	0x00, 0x00, 0xe4, 0x80, 0x00, 0x00, 0xe4, 0xa0,
	0xff, 0xff, 0x00, 0x00, 
};

//
// "rule"パイプラインは下記のピクセルシェーダ
//
// ruleShaderSrc[] =
//	"ps_1_4                                                             \n"
//	"def c0, 0, 0, 0, 0  // c0: zeros                                   \n"
//	"def c1, 1, 1, 1, 1  // c1: ones                                    \n"
//	"                    // c2: the slot for the threshould argument    \n"
//	"texld r0, t0        // r0 = samplerColor                           \n"
//	"texld r1, t1        // r1 = samplerRule                            \n"
//	"sub r1, r1, c2      // tmp = 1.0 - step(threshold, samplerRule);   \n"
//	"cmp r2, r1, c0, c1  // ...                                         \n"
//	"mov r0.a, r2.b      // samplerColor.a = tmp.b;                     \n";
//                       // return samplerColor;
//
static const unsigned char ruleShaderBin[] = {
	0x04, 0x01, 0xff, 0xff, 0x51, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x80, 0x3f,
	0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f,
	0x00, 0x00, 0x80, 0x3f, 0x42, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0xb0,
	0x42, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0f, 0x80,
	0x01, 0x00, 0xe4, 0xb0, 0x03, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0x80,
	0x02, 0x00, 0xe4, 0xa0, 0x58, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0x80,
	0x00, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0xe4, 0xa0,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80,
	0x02, 0x00, 0xaa, 0x80, 0xff, 0xff, 0x00, 0x00,
};

//
// "melt"パイプラインのピクセルシェーダ
//
// meltShaderSrc[] =
//	"ps_1_4                                                                  \n"
//	"def c0, 0, 0, 0, 0	  // c0: zeros                                         \n"
//	"def c1, 1, 1, 1, 1   // c1: ones                                          \n"
//	                      // c2: the slot for the threshould argument          \n"
//	"texld r0, t0         // r0 = samplerColor                                 \n"
//	"texld r1, t1         // r1 = samplerRule                                  \n"
//	                      // tmp = (1.0 - rule) + (threshold * 2.0 - 1.0);     \n"
//	"add r2, c2, c2       //   ... <<r2 = progress * 2.0>>                     \n"
//	"sub r2, r2, r1       //   ... <<r2 = r2 - rule>>                          \n"
//	                      // tmp = clamp(tmp);                                 \n"
//	"cmp r2, r2, r2, c0   //   ... <<r2 = r2 > 0 ? r2 : 0>>                    \n"
//	"sub r3, c1, r2       //   ... <<r3 = 1.0 - r3>>                           \n"
//	"cmp r2, r3, r2, c1   //   ... <<r2 = r3 > 0 ? r2 : c1>>                   \n"
//	"mov r0.a, r2.b       // samplerRule.a = tmp.b;                            \n";
//                        // return samplerRule.a;
//
static const unsigned char meltShaderBin[] = {
	0x04, 0x01, 0xff, 0xff, 0x51, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x80, 0x3f, 
	0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 
	0x00, 0x00, 0x80, 0x3f, 0x42, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0xb0, 
	0x42, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0f, 0x80, 
	0x01, 0x00, 0xe4, 0xb0, 0x02, 0x00, 0x00, 0x00, 
	0x02, 0x00, 0x0f, 0x80, 0x02, 0x00, 0xe4, 0xa0, 
	0x02, 0x00, 0xe4, 0xa0, 0x03, 0x00, 0x00, 0x00, 
	0x02, 0x00, 0x0f, 0x80, 0x02, 0x00, 0xe4, 0x80, 
	0x01, 0x00, 0xe4, 0x80, 0x58, 0x00, 0x00, 0x00, 
	0x02, 0x00, 0x0f, 0x80, 0x02, 0x00, 0xe4, 0x80, 
	0x02, 0x00, 0xe4, 0x80, 0x00, 0x00, 0xe4, 0xa0, 
	0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x0f, 0x80, 
	0x01, 0x00, 0xe4, 0xa0, 0x02, 0x00, 0xe4, 0x80, 
	0x58, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0f, 0x80, 
	0x03, 0x00, 0xe4, 0x80, 0x02, 0x00, 0xe4, 0x80, 
	0x01, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x08, 0x80, 0x02, 0x00, 0xaa, 0x80, 
	0xff, 0xff, 0x00, 0x00, 
};

//
// 前方参照
//
static VOID DrawPrimitives2D(int dst_left,
							 int dst_top,
							 int dst_width,
							 int dst_height,
							 struct image *src_image,
							 struct image *rule_image,
							 int src_left,
							 int src_top,
							 int src_width,
							 int src_height,
							 int alpha,
							 int pipeline);
static VOID DrawPrimitives3D(float x1,
							 float y1,
							 float x2,
							 float y2,
							 float x3,
							 float y3,
							 float x4,
							 float y4,
							 struct image *src_image,
							 struct image *rule_image,
							 int src_left,
							 int src_top,
							 int src_width,
							 int src_height,
							 int alpha,
							 int pipeline);
static BOOL UploadTextureIfNeeded(struct image *img);

//
// Direct3Dの初期化を行う
//
BOOL D3D9Initialize(HWND hWnd)
{
	HRESULT hResult;

	hMainWnd = hWnd;
	fDisplayOffsetX = 0.0f;
	fDisplayOffsetY = 0.0f;
	fScale = 1.0f;

	// Open d3d9.dll.
	LPDIRECT3D9 (__stdcall *pDirect3DCreate9)(DWORD) = NULL;
	HMODULE hModule = LoadLibrary(L"d3d9.dll");
	if (hModule == NULL)
		return FALSE;
	pDirect3DCreate9 = (LPDIRECT3D9 (__stdcall *)(DWORD))(void *)GetProcAddress(hModule, "Direct3DCreate9");
	if (pDirect3DCreate9 == NULL)
		return FALSE;

	// Direct3Dの作成を行う
	pD3D = pDirect3DCreate9(D3D_SDK_VERSION);
	if (pD3D == NULL)
    {
		log_api_error("Direct3DCreate9()");
        return FALSE;
    }

	// Direct3Dデバイスを作成する
	// (Windowed on boot)
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	hResult = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
								 D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp,
								 &pD3DDevice);
	if (FAILED(hResult))
	{
		pD3D->Release();
		pD3D = NULL;
		return FALSE;
	}

	// シェーダを作成する
	do {
		hResult = pD3DDevice->CreatePixelShader((DWORD *)dimShaderBin, &pDimShader);
		if (FAILED(hResult))
			break;

		hResult = pD3DDevice->CreatePixelShader((DWORD *)ruleShaderBin, &pRuleShader);
		if (FAILED(hResult))
			break;

		hResult = pD3DDevice->CreatePixelShader((DWORD *)meltShaderBin, &pMeltShader);
		if (FAILED(hResult))
			break;
	} while (0);
	if (FAILED(hResult))
	{
		log_api_error("Direct3DDevice9::CreatePixelShader()");
		pD3DDevice->Release();
		pD3DDevice = NULL;
		pD3D->Release();
		pD3D = NULL;
		return FALSE;
	}

	return TRUE;
}

//
// Direct3Dの終了処理を行う
//
VOID D3D9Cleanup(void)
{
	if (pMeltShader != NULL)
	{
		pD3DDevice->SetPixelShader(NULL);
		pMeltShader->Release();
		pMeltShader = NULL;
	}
	if (pRuleShader != NULL)
	{
		pD3DDevice->SetPixelShader(NULL);
		pRuleShader->Release();
		pRuleShader = NULL;
	}
	if (pD3DDevice != NULL)
	{
		pD3DDevice->Release();
		pD3DDevice = NULL;
	}
	if (pD3D != NULL)
	{
		pD3D->Release();
		pD3D = NULL;
	}
}

//
// ウィンドウをリサイズする
//
BOOL D3D9ResizeWindow(int nOffsetX, int nOffsetY, float scale)
{
	fDisplayOffsetX = (float)nOffsetX;
	fDisplayOffsetY = (float)nOffsetY;
	fScale = scale;

	if (pD3DDevice != NULL)
	{
		// Direct3Dデバイスをリセットする
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = TRUE;
		d3dpp.hDeviceWindow = hMainWnd;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		pD3DDevice->Reset(&d3dpp);
	}

	return TRUE;
}

//
// フレームの描画を開始する
//
VOID D3D9StartFrame(void)
{
	// クリアする
	pD3DDevice->Clear(0,
					  NULL,
					  D3DCLEAR_TARGET,
					  D3DCOLOR_RGBA(0, 0, 0, 255),
					  0,
					  0);

	// 描画を開始する
	pD3DDevice->BeginScene();
}

//
// フレームの描画を終了する
//
VOID D3D9EndFrame(void)
{
	// 描画を完了する
	pD3DDevice->EndScene();

	// 帯をクリアする
	RECT rcClient;
	GetClientRect(hMainWnd, &rcClient);
	if (fDisplayOffsetY > 0)
	{
		D3DRECT rc[2] = {
			{0, 0, rcClient.right, (LONG)fDisplayOffsetY},
			{0, (LONG)(rcClient.bottom - (int)fDisplayOffsetY), rcClient.right, rcClient.bottom}
		};			
		pD3DDevice->Clear(2, &rc[0], D3DCLEAR_TARGET, D3DCOLOR_RGBA(0, 0, 0, 255), 0, 0);
	}
	if (fDisplayOffsetX > 0)
	{
		D3DRECT rc[2] = {
			{0, 0, (LONG)fDisplayOffsetX, rcClient.bottom},
			{(LONG)(rcClient.right - (int)fDisplayOffsetX), 0, rcClient.right, rcClient.bottom}
		};			
		pD3DDevice->Clear(2, &rc[0], D3DCLEAR_TARGET, D3DCOLOR_RGBA(0, 0, 0, 255), 0, 0);
	}

	// 表示する
	if(pD3DDevice->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST)
	{
		// Direct3Dデバイスがロストしている場合
		if(pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			// Direct3Dデバイスをリセットする
			ZeroMemory(&d3dpp, sizeof(d3dpp));
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
			d3dpp.BackBufferCount = 1;
			d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			d3dpp.Windowed = TRUE;
			d3dpp.hDeviceWindow = hMainWnd;
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			pD3DDevice->Reset(&d3dpp);
		}
	}
}

VOID D3D9NotifyImageUpdate(struct image *img)
{
	img->need_upload = true;
}

VOID D3D9NotifyImageFree(struct image *img)
{
	IDirect3DTexture9 *pTex = (IDirect3DTexture9 *)img->texture;
	if(pTex == NULL)
		return;
	pTex->Release();
	img->texture = NULL;
}

VOID D3D9RenderImageNormal(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha)
{
	DrawPrimitives2D(dst_left, dst_top, dst_width, dst_height, src_image, NULL, src_left, src_top, src_width, src_height, alpha, PIPELINE_NORMAL);
}

VOID D3D9RenderImageAdd(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha)
{
	DrawPrimitives2D(dst_left, dst_top, dst_width, dst_height, src_image, NULL, src_left, src_top, src_width, src_height, alpha, PIPELINE_ADD);
}

VOID D3D9RenderImageDim(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha)
{
	DrawPrimitives2D(dst_left, dst_top, dst_width, dst_height, src_image, NULL, src_left, src_top, src_width, src_height, alpha, PIPELINE_DIM);
}

VOID D3D9RenderImageRule(struct image *src_image, struct image *rule_image, int threshold)
{
	DrawPrimitives2D(0, 0, src_image->width, src_image->height, src_image, rule_image, 0, 0, rule_image->width, rule_image->height, threshold, PIPELINE_RULE);
}

VOID D3D9RenderImageMelt(struct image *src_image, struct image *rule_image, int progress)
{
	DrawPrimitives2D(0, 0, src_image->width, src_image->height, src_image, rule_image, 0, 0, rule_image->width, rule_image->height, progress, PIPELINE_MELT);
}

VOID D3D9RenderImage3DNormal(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha)
{
	DrawPrimitives3D(x1, y1, x2, y2, x3, y3, x4, y4, src_image, NULL, src_left, src_top, src_width, src_height, alpha, PIPELINE_NORMAL);
}

VOID D3D9RenderImage3DAdd(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha)
{
	DrawPrimitives3D(x1, y1, x2, y2, x3, y3, x4, y4, src_image, NULL, src_left, src_top, src_width, src_height, alpha, PIPELINE_ADD);
}

static VOID DrawPrimitives2D(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, struct image *rule_image, int src_left, int src_top, int src_width, int src_height, int alpha, int pipeline)
{
	if (dst_width == -1)
		dst_width = src_image->width;
	if (dst_height == -1)
		dst_height = src_image->height;
	if (src_width == -1)
		src_width = src_image->width;
	if (src_height == -1)
		src_height = src_image->height;

	DrawPrimitives3D((float)dst_left,
					 (float)dst_top,
					 (float)(dst_left + dst_width - 1),
					 (float)dst_top,
					 (float)dst_left,
					 (float)(dst_top + dst_height - 1),
					 (float)(dst_left + dst_width - 1),
					 (float)(dst_top + dst_height - 1),
					 src_image,
					 rule_image,
					 src_left,
					 src_top,
					 src_width,
					 src_height,
					 alpha,
					 pipeline);
}

static VOID DrawPrimitives3D(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image *src_image, struct image *rule_image, int src_left, int src_top, int src_width, int src_height, int alpha, int pipeline)
{
	IDirect3DTexture9 *pTexColor = NULL;
	IDirect3DTexture9 *pTexRule = NULL;

	// テクスチャをアップロードする
	if (!UploadTextureIfNeeded(src_image))
		return;
	pTexColor = (IDirect3DTexture9 *)src_image->texture;
	if (rule_image != NULL) {
		if (!UploadTextureIfNeeded(rule_image))
			return;
		pTexRule = (IDirect3DTexture9 *)rule_image->texture;
	}

	float img_w = (float)src_image->width;
	float img_h = (float)src_image->height;

	Vertex v[4];

	// 左上
	v[0].x = x1 * fScale + fDisplayOffsetX - 0.5f;
	v[0].y = y1 * fScale + fDisplayOffsetY - 0.5f;
	v[0].z = 0.0f;
	v[0].rhw = 1.0f;
	v[0].u1 = (float)src_left / img_w;
	v[0].v1 = (float)src_top / img_h;
	v[0].u2 = v[0].u1;
	v[0].v2 = v[0].v1;
	v[0].color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	// 右上
	v[1].x = x2 * fScale + fDisplayOffsetX + 0.5f;
	v[1].y = y2 * fScale + fDisplayOffsetY - 0.5f;
	v[1].z = 0.0f;
	v[1].rhw = 1.0f;
	v[1].u1 = (float)(src_left + src_width) / img_w;
	v[1].v1 = (float)src_top / img_h;
	v[1].u2 = v[1].u1;
	v[1].v2 = v[1].v1;
	v[1].color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	// 左下
	v[2].x = x3 * fScale + fDisplayOffsetX - 0.5f;
	v[2].y = y3 * fScale + fDisplayOffsetY + 0.5f;
	v[2].z = 0.0f;
	v[2].rhw = 1.0f;
	v[2].u1 = (float)src_left / img_w;
	v[2].v1 = (float)(src_top + src_height) / img_h;
	v[2].u2 = v[2].u1;
	v[2].v2 = v[2].v1;
	v[2].color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	// 右下
	v[3].x = x4 * fScale + fDisplayOffsetX + 0.5f;
	v[3].y = y4 * fScale + fDisplayOffsetY + 0.5f;
	v[3].z = 0.0f;
	v[3].rhw = 1.0f;
	v[3].u1 = (float)(src_left + src_width) / img_w;
	v[3].v1 = (float)(src_top + src_height) / img_h;
	v[3].u2 = v[3].u1;
	v[3].v2 = v[3].v1;
	v[3].color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	FLOAT th = (float)alpha / 255.0f;
	FLOAT th4[4] = {th, th, th, th};

	switch (pipeline)
	{
	case PIPELINE_NORMAL:
		pD3DDevice->SetPixelShader(NULL);
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_COLOROP, D3DTOP_MODULATE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		break;
	case PIPELINE_ADD:
		pD3DDevice->SetPixelShader(NULL);
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_COLOROP, D3DTOP_MODULATE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		break;
	case PIPELINE_DIM:
		pD3DDevice->SetPixelShader(pDimShader);
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		th4[0] = th4[1] = th4[2] = 0.5f;
		pD3DDevice->SetPixelShaderConstantF(0, th4, 1);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_COLOROP, D3DTOP_MODULATE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		pD3DDevice->SetTextureStageState(0,	D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		break;
	case PIPELINE_RULE:
		pD3DDevice->SetPixelShader(pRuleShader);
		pD3DDevice->SetPixelShaderConstantF(2, th4, 1);
		pD3DDevice->SetTexture(1, pTexRule);
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	case PIPELINE_MELT:
		pD3DDevice->SetPixelShader(pMeltShader);
		pD3DDevice->SetPixelShaderConstantF(2, th4, 1);
		pD3DDevice->SetTexture(1, pTexRule);
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	default:
		assert(0);
		break;
	}

	// テクスチャ0を設定する
	pD3DDevice->SetTexture(0, pTexColor);
	pD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX2 | D3DFVF_DIFFUSE);

	// リニアフィルタを設定する
	pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	// UVラッピングを設定する
	pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	pD3DDevice->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pD3DDevice->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	// 描画する
	if(x1 == x2 && x2 == x3 && x3 == x4 &&
	   y1 == y2 && y2 == y3 && y3 == y4)
	{
		pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, v, sizeof(Vertex));
	}
	else if((x1 == x2 && x2 == x3 && x3 == x4) ||
			(y1 == y2 && y2 == y3 && y3 == y4))
	{
		pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, v + 1, sizeof(Vertex));
	}
	else
	{
		pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex));
	}
}

// テクスチャのアップロードを行う
static BOOL UploadTextureIfNeeded(struct image *img)
{
	HRESULT hResult;

	if (!img->need_upload)
		return TRUE;

	IDirect3DTexture9 *pTex = (IDirect3DTexture9 *)img->texture;
	if (pTex == NULL)
	{
		// Direct3Dテクスチャオブジェクトを作成する
		hResult = pD3DDevice->CreateTexture((UINT)img->width,
											(UINT)img->height,
											1, // mip map levels
											0, // usage
											D3DFMT_A8R8G8B8,
											D3DPOOL_MANAGED,
											&pTex,
											NULL);
		if (FAILED(hResult))
			return FALSE;

		img->texture = pTex;
	}

	// Direct3Dテクスチャオブジェクトの矩形をロックする
	D3DLOCKED_RECT lockedRect;
	hResult = pTex->LockRect(0, &lockedRect, NULL, 0);
	if (FAILED(hResult))
	{
		pTex->Release();
		img->texture = NULL;
		return FALSE;
	}

	// ピクセルデータをコピーする
	memcpy(lockedRect.pBits, img->pixels, (UINT)img->width * (UINT)img->height * sizeof(pixel_t));

	// Direct3Dテクスチャオブジェクトの矩形をアンロックする
	hResult = pTex->UnlockRect(0);
	if (FAILED(hResult))
	{
		pTex->Release();
		img->texture = NULL;
		return FALSE;
	}

	// アップロード完了した
	img->need_upload = false;
	return TRUE;
}

//
// [参考]
//  - シェーダ言語(アセンブリ or HLSL)をコンパイルするコード
//  - 実行時にコンパイルするにはd3dx9_43.dllのインストールが必要になる
//  - これがインストールされていなくても実行可能なようにしたい
//  - そこで、シェーダは開発者がコンパイルしてバイトコードをベタ書きすることにした
//  - 下記コードでコンパイルを行って、shader.txtの内容を利用すること
//  - 開発中のみリンカオプションで-ld3dx9とする
//
#if 0
#include <d3dx9.h>

void CompileShader(const char *pSrc, unsigned char *pDst, BOOL bHLSL)
{
	ID3DXBuffer *pShader;
	ID3DXBuffer *pError;

	if (!bHLSL)
	{
		// For pixel shader assembly
		if (FAILED(D3DXAssembleShader(pSrc, strlen(pSrc), 0, NULL, 0,
									  &pShader, &pError)))
		{
			log_api_error("D3DXAssembleShader");

			LPSTR pszError = (LPSTR)pError->GetBufferPointer();
			if (pszError != NULL)
				log_error("%s", pszError);

			exit(1);
		}
	}
	else
	{
		// For pixel shader HLSL
		if (FAILED(D3DXCompileShader(pSrc, strlen(pSrc) - 1,
									 NULL, NULL, "blur", "ps_2_0", 0,
									 &pShader, &pError, NULL)))
		{
			log_api_error("D3DXCompileShader");

			LPSTR pszError = (LPSTR)pError->GetBufferPointer();
			if (pszError != NULL)
				log_error("%s", pszError);

			exit(1);
		}
	}

	FILE *fp;
	fp = fopen("shader.txt", "w");
	if (fp == NULL)
		exit(1);

	int size = pShader->GetBufferSize();
	unsigned char *p = (unsigned char *)pShader->GetBufferPointer();
	for (int i=0; i<size; i++) {
		pDst[i] = p[i];
		fprintf(fp, "0x%02x, ", p[i]);
		if (i % 8 == 7)
			fprintf(fp, "\n");
	}

	fclose(fp);
}
#endif
