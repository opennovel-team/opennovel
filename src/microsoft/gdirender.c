/* -*- coding: utf-8; indent-tabs-mode: t; tab-width: 4; c-basic-offset: 4; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

/*
 * The Graphics HAL for GDI Software Rendering
 */

#include "../opennovel.h"
#include "d3drender.h"

static HWND hMainWnd;
static HDC hWndDC;
static struct image *pBackImage;
static HDC hBitmapDC;
static HBITMAP hBitmap;

BOOL GDIInitialize(HWND hWnd)
{
	hMainWnd = hWnd;

	// Get a device context for the window.
	hWndDC = GetDC(hMainWnd);

	// Create a device conetxt for RGBA32 bitmap.
	BITMAPINFO bi;
	memset(&bi, 0, sizeof(BITMAPINFO));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = conf_game_width;
	bi.bmiHeader.biHeight = -conf_game_height; /* Top-down */
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	hBitmapDC = CreateCompatibleDC(NULL);
	if(hBitmapDC == NULL)
		return FALSE;

	// Create a backing bitmap.
	pixel_t *pixels = NULL;
	hBitmap = CreateDIBSection(hBitmapDC, &bi, DIB_RGB_COLORS, (VOID **)&pixels, NULL, 0);
	if(hBitmap == NULL || pixels == NULL)
		return FALSE;
	SelectObject(hBitmapDC, hBitmap);

	// Create a image.
	pBackImage = create_image_with_pixels(conf_game_width, conf_game_height, pixels);
	if(pBackImage == NULL)
		return FALSE;

	return TRUE;
}

VOID GDICleanup(void)
{
}

BOOL GDIResizeWindow(int nOffsetX, int nOffsetY, float scale)
{
	UNUSED_PARAMETER(nOffsetX);
	UNUSED_PARAMETER(nOffsetY);
	UNUSED_PARAMETER(scale);
	return TRUE;
}

VOID GDIStartFrame(void)
{
}

VOID GDIEndFrame(void)
{
	BitBlt(hWndDC, 0, 0, conf_game_width, conf_game_height, hBitmapDC, 0, 0, SRCCOPY);
}

VOID GDINotifyImageUpdate(struct image *img)
{
	UNUSED_PARAMETER(img);
}

VOID GDINotifyImageFree(struct image *img)
{
	UNUSED_PARAMETER(img);
}

void GDIRenderImageNormal(
	int dst_left,				/* The X coordinate of the screen */
	int dst_top,				/* The Y coordinate of the screen */
	int dst_width,				/* The width of the destination rectangle */
	int dst_height,				/* The width of the destination rectangle */
	struct image *src_image,	/* [IN] an image to be rendered */
	int src_left,				/* The X coordinate of a source image */
	int src_top,				/* The Y coordinate of a source image */
	int src_width,				/* The width of the source rectangle */
	int src_height,				/* The height of the source rectangle */
	int alpha)					/* The alpha value (0 to 255) */
{
	UNUSED_PARAMETER(dst_width);
	UNUSED_PARAMETER(dst_height);

	if (dst_width == -1)
		dst_width = src_image->width;
	if (dst_height == -1)
		dst_height = src_image->height;
	if (src_width == -1)
		src_width = src_image->width;
	if (src_height == -1)
		src_height = src_image->height;

	draw_image_fast(pBackImage,
					dst_left,
					dst_top,
					src_image,
					src_width,
					src_height,
					src_left,
					src_top,
					alpha);
}

void GDIRenderImageAdd(
	int dst_left,				/* The X coordinate of the screen */
	int dst_top,				/* The Y coordinate of the screen */
	int dst_width,				/* The width of the destination rectangle */
	int dst_height,				/* The width of the destination rectangle */
	struct image *src_image,	/* [IN] an image to be rendered */
	int src_left,				/* The X coordinate of a source image */
	int src_top,				/* The Y coordinate of a source image */
	int src_width,				/* The width of the source rectangle */
	int src_height,				/* The height of the source rectangle */
	int alpha)					/* The alpha value (0 to 255) */
{
	UNUSED_PARAMETER(dst_width);
	UNUSED_PARAMETER(dst_height);

	if (dst_width == -1)
		dst_width = src_image->width;
	if (dst_height == -1)
		dst_height = src_image->height;
	if (src_width == -1)
		src_width = src_image->width;
	if (src_height == -1)
		src_height = src_image->height;

	draw_image_add(pBackImage,
				   dst_left,
				   dst_top,
				   src_image,
				   src_width,
				   src_height,
				   src_left,
				   src_top,
				   alpha);
}

void GDIRenderImageDim(
	int dst_left,				/* The X coordinate of the screen */
	int dst_top,				/* The Y coordinate of the screen */
	int dst_width,				/* The width of the destination rectangle */
	int dst_height,				/* The width of the destination rectangle */
	struct image *src_image,	/* [IN] an image to be rendered */
	int src_left,				/* The X coordinate of a source image */
	int src_top,				/* The Y coordinate of a source image */
	int src_width,				/* The width of the source rectangle */
	int src_height,				/* The height of the source rectangle */
	int alpha)					/* The alpha value (0 to 255) */
{
	UNUSED_PARAMETER(dst_width);
	UNUSED_PARAMETER(dst_height);

	if (dst_width == -1)
		dst_width = src_image->width;
	if (dst_height == -1)
		dst_height = src_image->height;
	if (src_width == -1)
		src_width = src_image->width;
	if (src_height == -1)
		src_height = src_image->height;

	draw_image_dim(pBackImage,
				   dst_left,
				   dst_top,
				   src_image,
				   src_width,
				   src_height,
				   src_left,
				   src_top,
				   alpha);
}

void GDIRenderImageRule(
	struct image *src_image,
	struct image *rule_image,
	int threshold)
{
	draw_image_rule(pBackImage,
					src_image,
					rule_image,
					threshold);
}

void GDIRenderImageMelt(
	struct image *src_image,
	struct image *rule_image,
	int progress)
{
	draw_image_melt(pBackImage,
					src_image,
					rule_image,
					progress);
}

VOID GDIRenderImage3DNormal(
	float x1,
	float y1,
	float x2,
	float y2,
	float x3,
	float y3,
	float x4,
	float y4,
	struct image *src_image,
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha)
{
	UNUSED_PARAMETER(x1);
	UNUSED_PARAMETER(y1);
	UNUSED_PARAMETER(x2);
	UNUSED_PARAMETER(y2);
	UNUSED_PARAMETER(x3);
	UNUSED_PARAMETER(y3);
	UNUSED_PARAMETER(x4);
	UNUSED_PARAMETER(y4);
	UNUSED_PARAMETER(src_image);
	UNUSED_PARAMETER(src_left);
	UNUSED_PARAMETER(src_top);
	UNUSED_PARAMETER(src_width);
	UNUSED_PARAMETER(src_height);
	UNUSED_PARAMETER(alpha);
}

VOID GDIRenderImage3DAdd(
	float x1,
	float y1,
	float x2,
	float y2,
	float x3,
	float y3,
	float x4,
	float y4,
	struct image *src_image,
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha)
{
	UNUSED_PARAMETER(x1);
	UNUSED_PARAMETER(y1);
	UNUSED_PARAMETER(x2);
	UNUSED_PARAMETER(y2);
	UNUSED_PARAMETER(x3);
	UNUSED_PARAMETER(y3);
	UNUSED_PARAMETER(x4);
	UNUSED_PARAMETER(y4);
	UNUSED_PARAMETER(src_image);
	UNUSED_PARAMETER(src_left);
	UNUSED_PARAMETER(src_top);
	UNUSED_PARAMETER(src_width);
	UNUSED_PARAMETER(src_height);
	UNUSED_PARAMETER(alpha);
}
