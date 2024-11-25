/* -*- tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

/*
 * OpenGL Graphics
 */

#if defined(USE_X11_VULKAN)

/* Xlib */
#include <X11/Xlib.h>

/* Base */
#include "../opennovel.h"
#include "x11main.h"

/* Vulkan Graphics HAL */
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xlib.h>
#include "../khronos/vkrender.h"

static const char* const ext_names[] = {
	"VK_KHR_surface",
	"VK_KHR_xlib_surface",
};

static VkInstance instance;
static VkSurfaceKHR surface;

/* Forward Declaration */
static bool create_window(void);

bool init_x11_graphics(void)
{
	VkApplicationInfo app_info;
	VkInstanceCreateInfo create_info;
	VkXlibSurfaceCreateInfoKHR surface_create_info;
	VkResult (*vkCreateXlibSurfaceKHR_)(VkInstance, const VkXlibSurfaceCreateInfoKHR *, const VkAllocationCallbacks *, VkSurfaceKHR *);

	/*
	 * Create a X11 window.
	 */
	if (create_window())
		return false;

	/*
	 * Create a Vulkan instance.
	 */

	memset(&app_info, 0, sizeof(app_info));
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "OpenNovel";
	app_info.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	app_info.pEngineName = "OpenNovel";
	app_info.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	memset(&create_info, 0, sizeof(create_info));
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;
	create_info.enabledExtensionCount = sizeof(ext_names) / sizeof(const char*);
	create_info.ppEnabledExtensionNames = ext_names;

	vkCreateInstance(&create_info, NULL, &instance);

	/*
	 * Create a Vulkan surface.
	 */

	memset(&surface_create_info, 0, sizeof(surface_create_info));
	surface_create_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
	surface_create_info.dpy = display;
	surface_create_info.window = window;

	vkCreateXlibSurfaceKHR_ = (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(instance, "vkCreateXlibSurfaceKHR");
	vkCreateXlibSurfaceKHR_(instance, &surface_create_info, NULL, &surface);

	/*
	 * Initialize the Vulkan renderer.
	 */

	if (!init_vulkan(instance, surface))
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
	vkDestroySurfaceKHR(instance, surface, NULL);
	vkDestroyInstance(instance, NULL);
}

void start_x11_rendering(void)
{
	/* TODO */
}

void end_x11_rendering(void)
{
	/* TODO */
}

void notify_image_update(struct image *img)
{
	vulkan_notify_image_update(img);
}

void notify_image_free(struct image *img)
{
	vulkan_notify_image_free(img);
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
	vulkan_render_image_normal(dst_left,
				   dst_top,
				   dst_width,
				   dst_height,
				   src_image,
				   src_left,
				   src_top,
				   src_width,
				   src_height,
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
	vulkan_render_image_add(dst_left,
				dst_top,
				dst_width,
				dst_height,
				src_image,
				src_left,
				src_top,
				src_width,
				src_height,
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
	vulkan_render_image_dim(dst_left,
				dst_top,
				dst_width,
				dst_height,
				src_image,
				src_left,
				src_top,
				src_width,
				src_height,
				alpha);
}

void render_image_rule(struct image *src_img,
		       struct image *rule_img,
		       int threshold)
{
	vulkan_render_image_rule(src_img, rule_img, threshold);
}

void render_image_melt(struct image *src_img,
		       struct image *rule_img,
		       int progress)
{
	vulkan_render_image_melt(src_img, rule_img, progress);
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
	vulkan_render_image_3d_normal(x1,
				      y1,
				      x2,
				      y2,
				      x3,
				      y3,
				      x4,
				      y4,
				      src_image,
				      src_left,
				      src_top,
				      src_width,
				      src_height,
				      alpha);
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
	vulkan_render_image_3d_add(x1,
				   y1,
				   x2,
				   y2,
				   x3,
				   y3,
				   x4,
				   y4,
				   src_image,
				   src_left,
				   src_top,
				   src_width,
				   src_height,
				   alpha);
}

#endif /* defined(USE_X11_VULKAN) */
