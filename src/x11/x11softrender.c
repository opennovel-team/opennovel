/* -*- tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

/*
 * Soft Rendering Graphics
 */

#if defined(USE_X11_SOFTRENDER)

/* Xlib */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/* Base */
#include "../opennovel.h"
#include "x11main.h"

/* POSIX */
#include <unistd.h>	/* posix_memalign() */

static XImage *ximage;
struct image *back_image;

static bool create_window(void);

bool init_x11_graphics(void)
{
	XVisualInfo vi;
	pixel_t *pixels;
	int screen;

	/* Allocate an image buffer which may be freed by XDestroyImage(). */
	if (posix_memalign((void **)&pixels, 64,
			   (size_t)(conf_game_width * conf_game_height * BPP / 8)) != 0)
		return false;

	/* Create a back image. */
	back_image = create_image_with_pixels(conf_game_width, conf_game_height, pixels);
	if (back_image == NULL) {
		free(pixels);
		return false;
	}

	/* Get a 32bpp Visual. */
	screen = DefaultScreen(display);
	if (!XMatchVisualInfo(display, screen, BPP, TrueColor, &vi)) {
		log_error("Your X server is not capable of 32bpp mode.\n");
		destroy_image(back_image);
		free(pixels);
		return false;
	}

	/* Create an XImage object that holds the back image buffer. */
	ximage = XCreateImage(display, vi.visual, DEPTH, ZPixmap, 0,
			      (char *)pixels,
			      (unsigned int)conf_game_width,
			      (unsigned int)conf_game_height,
			      BPP,
			      conf_game_width * BPP / 8);
	if (ximage == NULL) {
		destroy_image(back_image);
		free(pixels);
		return false;
	}

	/* Create a window. */
	if (!create_window())
		return false;

	return true;
}

static bool create_window(void)
{
	Window root;
	unsigned long black, white;
	int screen;

	/* Get display information. */
	screen = DefaultScreen(display);
	root  = RootWindow(display, screen);
	black = BlackPixel(display, screen);
	white = WhitePixel(display, screen);

	/* Create a window. */
	window = XCreateSimpleWindow(display, root, 0, 0,
				     (unsigned int)conf_game_width,
				     (unsigned int)conf_game_height,
				     1, black, white);
	if (window == BadAlloc || window == BadMatch || window == BadValue || window == BadWindow) {
		log_api_error("XCreateSimpleWindow");
		return false;
	}

	return true;
}

void cleanup_x11_graphics(void)
{
	if (ximage != NULL) {
		XDestroyImage(ximage);
		ximage = NULL;
	}

	if (back_image != NULL) {
		destroy_image(back_image);
		back_image = NULL;
	}
}

void start_x11_rendering(void)
{
	clear_image_black(back_image);
}

void end_x11_rendering(void)
{
	GC gc = XCreateGC(display, window, 0, 0);
	XPutImage(display,
		  window,
		  gc,
		  ximage,
		  0,
		  0,
		  0,
		  0,
		  (unsigned int)conf_game_width,
		  (unsigned int)conf_game_height);
	XFreeGC(display, gc);
}

void notify_image_update(struct image *img)
{
	UNUSED_PARAMETER(img);
}

void notify_image_free(struct image *img)
{
	UNUSED_PARAMETER(img);
}

void render_image_normal(int dst_left,
			 int dst_top,
			 int dst_width,
			 int dst_height,
			 struct image *src_image,
			 int src_left,
			 int src_top,
			 int src_width,
			 int src_height,
			 int alpha)
{
	if (dst_width == -1)
		dst_width = src_image->width;
	if (dst_height == -1)
		dst_height = src_image->height;
	if (src_width == -1)
		src_width = src_image->width;
	if (src_height == -1)
		src_height = src_image->height;

	draw_image_fast(back_image,
			dst_left,
			dst_top,
			src_image,
			src_width,
			src_height,
			src_left,
			src_top,
			alpha);
}

void render_image_add(int dst_left,
		      int dst_top,
		      int dst_width,
		      int dst_height,
		      struct image *src_image,
		      int src_left,
		      int src_top,
		      int src_width,
		      int src_height,
		      int alpha)
{
	if (dst_width == -1)
		dst_width = src_image->width;
	if (dst_height == -1)
		dst_height = src_image->height;
	if (src_width == -1)
		src_width = src_image->width;
	if (src_height == -1)
		src_height = src_image->height;

	draw_image_add(back_image,
		       dst_left,
		       dst_top,
		       src_image,
		       src_width,
		       src_height,
		       src_left,
		       src_top,
		       alpha);
}

void render_image_dim(int dst_left,
		      int dst_top,
		      int dst_width,
		      int dst_height,
		      struct image *src_image,
		      int src_left,
		      int src_top,
		      int src_width,
		      int src_height,
		      int alpha)
{
	if (dst_width == -1)
		dst_width = src_image->width;
	if (dst_height == -1)
		dst_height = src_image->height;
	if (src_width == -1)
		src_width = src_image->width;
	if (src_height == -1)
		src_height = src_image->height;

	draw_image_dim(back_image,
		       dst_left,
		       dst_top,
		       src_image,
		       src_width,
		       src_height,
		       src_left,
		       src_top,
		       alpha);
}

void render_image_rule(struct image *src_img,
		       struct image *rule_img,
		       int threshold)
{
	draw_image_rule(back_image, src_img, rule_img, threshold);
}

void render_image_melt(struct image *src_img,
		       struct image *rule_img,
		       int progress)
{
	draw_image_melt(back_image, src_img, rule_img, progress);
}

void
render_image_3d_normal(
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

void
render_image_3d_add(
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

#endif /* defined(USE_X11_SOFTRENDER) */
