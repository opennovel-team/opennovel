/* -*- coding: utf-8; indent-tabs-mode: t; tab-width: 4; c-basic-offset: 4; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

/*
 * The Graphics HAL for Windows
 */

#ifndef OPENNOVEL_D3DRENDER_H
#define OPENNOVEL_D3DRENDER_H

#include "../opennovel.h"

#include <windows.h>

/* Public */
BOOL D3DInitialize(HWND hWnd, BOOL bForceD3D9);
VOID D3DCleanup(void);
BOOL D3DResizeWindow(int nOffsetX, int nOffsetY, float scale);
VOID D3DStartFrame(void);
VOID D3DEndFrame(void);
BOOL D3DRedraw(void);
BOOL D3DIsSoftRendering(void);

/* Internal */
BOOL D3D12Initialize(HWND hWnd);
BOOL D3D11Initialize(HWND hWnd);
BOOL D3D9Initialize(HWND hWnd);
BOOL GDIInitialize(HWND hWnd);
VOID D3D12Cleanup(void);
VOID D3D11Cleanup(void);
VOID D3D9Cleanup(void);
VOID GDICleanup(void);
BOOL D3D12ResizeWindow(int nOffsetX, int nOffsetY, float scale);
BOOL D3D11ResizeWindow(int nOffsetX, int nOffsetY, float scale);
BOOL D3D9ResizeWindow(int nOffsetX, int nOffsetY, float scale);
BOOL GDIResizeWindow(int nOffsetX, int nOffsetY, float scale);
VOID D3D12StartFrame(void);
VOID D3D11StartFrame(void);
VOID D3D9StartFrame(void);
VOID GDIStartFrame(void);
VOID D3D12EndFrame(void);
VOID D3D11EndFrame(void);
VOID D3D9EndFrame(void);
VOID GDIEndFrame(void);
VOID D3D12NotifyImageUpdate(struct image* img);
VOID D3D11NotifyImageUpdate(struct image *img);
VOID D3D9NotifyImageUpdate(struct image *img);
VOID GDINotifyImageUpdate(struct image *img);
VOID D3D12NotifyImageFree(struct image* img);
VOID D3D11NotifyImageFree(struct image* img);
VOID D3D9NotifyImageFree(struct image *img);
VOID GDINotifyImageFree(struct image *img);
VOID D3D12RenderImageNormal(int dst_left, int dst_top, int dst_width, int dst_height, struct image* src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D11RenderImageNormal(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D9RenderImageNormal(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID GDIRenderImageNormal(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D12RenderImageAdd(int dst_left, int dst_top, int dst_width, int dst_height, struct image* src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D11RenderImageAdd(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D9RenderImageAdd(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID GDIRenderImageAdd(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D12RenderImageDim(int dst_left, int dst_top, int dst_width, int dst_height, struct image* src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D11RenderImageDim(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D9RenderImageDim(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID GDIRenderImageDim(int dst_left, int dst_top, int dst_width, int dst_height, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D12RenderImageRule(struct image* src_image, struct image* rule_image, int threshold);
VOID D3D11RenderImageRule(struct image *src_image, struct image *rule_image, int threshold);
VOID D3D9RenderImageRule(struct image *src_image, struct image *rule_image, int threshold);
VOID GDIRenderImageRule(struct image *src_image, struct image *rule_image, int threshold);
VOID D3D12RenderImageMelt(struct image* src_image, struct image* rule_image, int progress);
VOID D3D11RenderImageMelt(struct image *src_image, struct image *rule_image, int progress);
VOID D3D9RenderImageMelt(struct image *src_image, struct image *rule_image, int progress);
VOID GDIRenderImageMelt(struct image *src_image, struct image *rule_image, int progress);
VOID D3D12RenderImage3DNormal(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image* src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D11RenderImage3DNormal(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image* src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D9RenderImage3DNormal(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID GDIRenderImage3DNormal(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D12RenderImage3DAdd(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image* src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D11RenderImage3DAdd(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID D3D9RenderImade3DAdd(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);
VOID GDIRenderImade3DAdd(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, struct image *src_image, int src_left, int src_top, int src_width, int src_height, int alpha);

#endif
