/* -*- tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

/*
 * HAL for Emscripten (Local File Version)
 */

/* OpenNovel Base */
#include "opennovel.h"

/* OpenNovel Graphics HAL for OpenGL */
#include "khronos/glrender.h"

/* OpenNovel Sound HAL for Emscripten OpenAL */
#include "wasm/alsound.h"

/* Emscripten Core */
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

/* Emscripten POSIX Emulation */
#include <sys/types.h>
#include <sys/stat.h>	/* stat(), mkdir() */
#include <sys/time.h>	/* gettimeofday() */

/*
 * Constants
 */

/* Frame Milli Seconds */
#define FRAME_MILLI	33

/*
 * Variables
 */

/* Touch Position */
static int touch_start_x;
static int touch_start_y;
static int touch_last_y;
static bool is_continuous_swipe_enabled;

/*
 * Forward Declarations
 */
static void loop_iter(void *userData);
static EM_BOOL cb_mousemove(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
static EM_BOOL cb_mousedown(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
static EM_BOOL cb_mouseup(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
static EM_BOOL cb_wheel(int eventType, const EmscriptenWheelEvent *wheelEvent, void *userData);
static EM_BOOL cb_keydown(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);
static EM_BOOL cb_keyup(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);
static int get_keycode(const char *key);
static EM_BOOL cb_touchstart(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData);
static EM_BOOL cb_touchmove(int eventType, const EmscriptenTouchEvent *touchEvent,void *userData);
static EM_BOOL cb_touchend(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData);
static EM_BOOL cb_touchcancel(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData);

/*
 * Main
 */
int main(void)
{
	/* Keep the thread alive and will receive events. */
	emscripten_exit_with_live_runtime();
	return 0;
}

/*
 * Startup
 */
EMSCRIPTEN_KEEPALIVE
void start_engine(void)
{
	/* Initialize the file system. */
	if(!init_file())
		return;

	/* Initialize the config. */
	if(!init_conf())
		return;

	/* Initialize the OpenAL sound subsystem. */
	if (!init_openal())
		return;

	/* Set the rendering canvas size. */
	emscripten_set_canvas_element_size("canvas", conf_game_width, conf_game_height);
	EM_ASM_({ onResizeWindow(); });

	/* Initialize the OpenGL rendering subsystem. */
	EmscriptenWebGLContextAttributes attr;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
	emscripten_webgl_init_context_attributes(&attr);
	attr.majorVersion = 2;
	attr.minorVersion = 0;
	context = emscripten_webgl_create_context("canvas", &attr);
	emscripten_webgl_make_context_current(context);
	if (!init_opengl())
		return;

	/* Execute the startup event. */
	if(!on_event_init())
		return;

	/* Register input events. */
	emscripten_set_mousedown_callback("canvas", 0, true, cb_mousedown);
	emscripten_set_mouseup_callback("canvas", 0, true, cb_mouseup);
	emscripten_set_mousemove_callback("canvas", 0, true, cb_mousemove);
	emscripten_set_wheel_callback("canvas", 0, true, cb_wheel);
	emscripten_set_keydown_callback("canvas", 0, true, cb_keydown);
	emscripten_set_keyup_callback("canvas", 0, true, cb_keyup);
	emscripten_set_touchstart_callback("canvas", 0, true, cb_touchstart);
	emscripten_set_touchmove_callback("canvas", 0, true, cb_touchmove);
	emscripten_set_touchend_callback("canvas", 0, true, cb_touchend);
	emscripten_set_touchcancel_callback("canvas", 0, true, cb_touchcancel);

	/* Register other events. */
	EM_ASM_({
		window.addEventListener('resize', onResizeWindow);
		document.addEventListener('visibilitychange', function () {
			if(document.visibilityState === 'visible') {
				Module.ccall('setVisible');
				document.getElementById('canvas').focus();
			} else if(document.visibilityState === 'hidden') {
				Module.ccall('setHidden');
			}
		});
		document.getElementById('canvas').addEventListener('mouseleave', function () {
			Module.ccall('mouseLeave');
		});
	});

	/* Reserve the first frame callback. */
	emscripten_async_call(loop_iter, NULL, FRAME_MILLI);
}

EM_JS(void, onResizeWindow, (void),
{
	var canvas = document.getElementById('canvas');
	var cw = canvas.width;
	var ch = canvas.height;
	var aspect = cw / ch;
	var winw = window.innerWidth;
	var winh = window.innerHeight;
	var w = winw;
	var h = winw / aspect;
	if(h > winh) {
		h = winh;
		w = winh * aspect;
	}
	canvas.style.width = w + 'px';
	canvas.style.height = h + 'px';
	canvas.focus();
});

/* Run a frame. */
static void loop_iter(void *userData)
{
	static bool is_flip_pending = false;

	/* Do sound buffer filling. */
	fill_sound_buffer();

	/*
	 * Start a rendering.
	 *  - On Chrome, glFlush() seems to be called on "await" for a file I/O
	 *  - This causes flickering
	 *  - We avoid calling glClear() through opengl_start_rendering() here
	 *  - See also finish_frame_io()
	 */
	/* opengl_start_rendering(); */

	/* Do a frame event. */
	on_event_frame();

	/* Finish a rendering. */
	opengl_end_rendering();

	/* Reserve the next frame callback. */
	emscripten_async_call(loop_iter, NULL, FRAME_MILLI);
}

/* mousemove callback */
static EM_BOOL cb_mousemove(int eventType,
			    const EmscriptenMouseEvent *mouseEvent,
			    void *userData)
{
	double w, h, scale;
	int x, y;

	/*
	 * Get the "CSS" size of the rendering canvas
	 *  - It's not a visible size of the canvas
	 */
	emscripten_get_element_css_size("canvas", &w, &h);

	/* Scale a mouse position. */
	scale = w / (double)conf_game_width;
	x = (int)((double)mouseEvent->targetX / scale);
	y = (int)((double)mouseEvent->targetY / scale);

	/* Call the event handler. */
	on_event_mouse_move(x, y);

	return EM_TRUE;
}

/* mousedown callback */
static EM_BOOL cb_mousedown(int eventType,
			    const EmscriptenMouseEvent *mouseEvent,
			    void *userData)
{
	double w, h, scale;
	int x, y, button;

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)conf_game_width;
	x = (int)((double)mouseEvent->targetX / scale);
	y = (int)((double)mouseEvent->targetY / scale);

	if (mouseEvent->button == 0)
		button = MOUSE_LEFT;
	else
		button = MOUSE_RIGHT;

	/* Call the event handler. */
	on_event_mouse_press(button, x, y);

	return EM_TRUE;
}

/* mouseup callback */
static EM_BOOL cb_mouseup(int eventType,
			    const EmscriptenMouseEvent *mouseEvent,
			    void *userData)
{
	double w, h, scale;
	int x, y, button;

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)conf_game_width;
	x = (int)((double)mouseEvent->targetX / scale);
	y = (int)((double)mouseEvent->targetY / scale);

	if (mouseEvent->button == 0)
		button = MOUSE_LEFT;
	else
		button = MOUSE_RIGHT;

	/* Call the event handler. */
	on_event_mouse_release(button, x, y);

	return EM_TRUE;
}

/* wheel callback */
static EM_BOOL cb_wheel(int eventType,
			const EmscriptenWheelEvent *wheelEvent,
			void *userData)
{
	if (wheelEvent->deltaY > 0) {
		on_event_key_press(KEY_DOWN);
		on_event_key_release(KEY_DOWN);
	} else {
		on_event_key_press(KEY_UP);
		on_event_key_release(KEY_UP);
	}
	return EM_TRUE;
}

/* keydown callback */
static EM_BOOL cb_keydown(int eventType,
			  const EmscriptenKeyboardEvent *keyEvent,
			  void *userData)
{
	int keycode;

	keycode = get_keycode(keyEvent->key);
	if (keycode == -1)
		return EM_TRUE;

	on_event_key_press(keycode);
	return EM_TRUE;
}

/* keyup callback */
static EM_BOOL cb_keyup(int eventType,
			const EmscriptenKeyboardEvent *keyEvent,
			void *userData)
{
	int keycode;

	keycode = get_keycode(keyEvent->key);
	if (keycode == -1)
		return EM_TRUE;

	on_event_key_release(keycode);
	return EM_TRUE;
}

/* Get a keycode from a keysym. */
static int get_keycode(const char *key)
{
	if (strcmp(key, "Enter") == 0) {
		return KEY_RETURN;
	} else if (strcmp(key, " ") == 0) {
		return KEY_SPACE;
	} else if (strcmp(key, "Control") == 0) {
		return KEY_CONTROL;
	} else if (strcmp(key, "ArrowUp") == 0) {
		return KEY_UP;
	} else if (strcmp(key, "ArrowDown") == 0) {
		return KEY_DOWN;
	}
	return -1;
}

/* touchstart callback */
static EM_BOOL cb_touchstart(
	int eventType,
	const EmscriptenTouchEvent *touchEvent,
	void *userData)
{
	double w, h, scale;
	int x, y;

	touch_start_x = touchEvent->touches[0].targetX;
	touch_start_y = touchEvent->touches[0].targetY;
	touch_last_y = touchEvent->touches[0].targetY;

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)conf_game_width;
	x = (int)((double)touchEvent->touches[0].targetX / scale);
	y = (int)((double)touchEvent->touches[0].targetY / scale);

	/* Call the event handler. */
	on_event_mouse_press(MOUSE_LEFT, x, y);

	return EM_TRUE;
}

/* touchmove callback */
static EM_BOOL cb_touchmove(
	int eventType,
	const EmscriptenTouchEvent *touchEvent,
	void *userData)
{
	const int LINE_HEIGHT = 10;
	double w, h, scale;
	int delta, x, y;

	delta = touchEvent->touches[0].targetY - touch_last_y;
	touch_last_y = touchEvent->touches[0].targetY;

	if (delta > LINE_HEIGHT) {
		on_event_key_press(KEY_DOWN);
		on_event_key_release(KEY_DOWN);
	} else if (delta < -LINE_HEIGHT) {
		on_event_key_press(KEY_UP);
		on_event_key_release(KEY_UP);
	}

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)conf_game_width;
	x = (int)((double)touchEvent->touches[0].targetX / scale);
	y = (int)((double)touchEvent->touches[0].targetY / scale);

	/* Call the event handler. */
	on_event_mouse_move(x, y);

	return EM_TRUE;
}

/* touchend callback */
static EM_BOOL cb_touchend(
	int eventType,
	const EmscriptenTouchEvent *touchEvent,
	void *userData)
{
	const int OFS = 10;
	double w, h, scale;
	int x, y;

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)conf_game_width;
	x = (int)((double)touchEvent->touches[0].targetX / scale);
	y = (int)((double)touchEvent->touches[0].targetY / scale);

	/* Call the event handler. */
	on_event_mouse_move(x, y);

	/* Consider a two-finger tap as a right-click. */
	if (touchEvent->numTouches == 2) {
		on_event_mouse_press(MOUSE_RIGHT, x, y);
		on_event_mouse_release(MOUSE_RIGHT, x, y);
		return EM_TRUE;
	}

	/* Consider a one-finger tap as a left-click. */
	if (abs(touchEvent->touches[0].targetX - touch_start_x) < OFS &&
	    abs(touchEvent->touches[0].targetY - touch_start_y) < OFS) {
		on_event_mouse_release(MOUSE_LEFT, x, y);
		return EM_TRUE;
	}
	
	return EM_TRUE;
}

/* touchcancel callback */
static EM_BOOL cb_touchcancel(int eventType,
			      const EmscriptenTouchEvent *touchEvent,
			      void *userData)
{
	on_event_mouse_move(-1, -1);

	return EM_TRUE;
}

/*
 * Callback from JavaScript
 */

/* Resize the canvas. */
EM_JS(void, resizeWindow, (void), {
	canvas = document.getElementById('canvas');
	cw = canvas.width;
	ch = canvas.height;
	aspect = cw / ch;
	winw = window.innerWidth;
	winh = window.innerHeight;
	w = winw;
	h = winw / aspect;
	if(h > winh) {
		h = winh;
		w = winh * aspect;
	}
	canvas.style.width = w + 'px';
	canvas.style.height = h + 'px';
	canvas.focus();
});

/* Callback when a project is loaded. */
EMSCRIPTEN_KEEPALIVE void onLoadProject(void)
{
	start_engine();
}

/* Callback when a tab is shown. */
EMSCRIPTEN_KEEPALIVE void setVisible(void)
{
	resume_sound();
}

/* Callback when a tab is hidden. */
EMSCRIPTEN_KEEPALIVE void setHidden(void)
{
	pause_sound();
}

/*
 * HAL API
 */

bool log_info(const char *s, ...)
{
	char buf[1024];

	va_list ap;
	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	EM_ASM({
		alert(UTF8ToString($0));
	}, buf);

	return true;
}

bool log_warn(const char *s, ...)
{
	char buf[1024];

	va_list ap;
	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	EM_ASM({
		alert(UTF8ToString($0));
	}, buf);

	return true;
}

bool log_error(const char *s, ...)
{
	char buf[1024];

	va_list ap;
	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	EM_ASM({
		alert(UTF8ToString($0));
	}, buf);

	return true;
}

void notify_image_update(struct image *img)
{
	fill_sound_buffer();
	opengl_notify_image_update(img);
	fill_sound_buffer();
}

void notify_image_free(struct image *img)
{
	fill_sound_buffer();
	opengl_notify_image_free(img);
	fill_sound_buffer();
}

void render_image_normal(
	int dst_left,
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
	opengl_render_image_normal(dst_left, dst_top, dst_width, dst_height, src_image, src_left, src_top, src_width, src_height, alpha);
}

void render_image_add(
	int dst_left,
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
	opengl_render_image_add(dst_left, dst_top, dst_width, dst_height, src_image, src_left, src_top, src_width, src_height, alpha);
}

void render_image_dim(
	int dst_left,
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
	opengl_render_image_dim(dst_left, dst_top, dst_width, dst_height, src_image, src_left, src_top, src_width, src_height, alpha);
}

void render_image_rule(
	struct image *src_img,
	struct image *rule_img,
	int threshold)
{
	opengl_render_image_rule(src_img, rule_img, threshold);
}

void render_image_melt(
	struct image *src_img,
	struct image *rule_img,
	int threshold)
{
	opengl_render_image_melt(src_img, rule_img, threshold);
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
	opengl_render_image_3d_normal(x1,
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
	opengl_render_image_3d_add(x1,
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

bool make_sav_dir(void)
{
	/* stub */
	return true;
}

char *make_valid_path(const char *dir, const char *fname)
{
	/* stub */
	return strdup("");
}

void reset_lap_timer(uint64_t *t)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	*t = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

uint64_t get_lap_timer_millisec(uint64_t *t)
{
	struct timeval tv;
	uint64_t end;
	
	gettimeofday(&tv, NULL);

	end = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);

	return (uint64_t)(end - *t);
}

bool play_video(const char *fname, bool is_skippable)
{
	char *path;

	path = make_valid_path(MOV_DIR, fname);

	EM_ASM_({
		document.getElementById("canvas").style.display = "none";

		var v = document.getElementById("video");
		v.style.display = "block";
		v.src = s2GetFileURL(Module.UTF8ToString($0));
		v.load();
		v.addEventListener('ended', function() {
			document.getElementById("canvas").style.display = "block";
			document.getElementById("video").style.display = "none";
		});
		v.play();
	}, path);

	free(path);

	return true;
}

void stop_video(void)
{
	EM_ASM_({
		var c = document.getElementById("canvas");
		c.style.display = "block";

		var v = document.getElementById("video");
		v.style.display = "none";
		v.pause();
		v.src = "";
		v.load();
	});
}

bool is_video_playing(void)
{
	int ended;

	ended = EM_ASM_INT({
		var v = document.getElementById("video");
		return v.ended;
	});

	return !ended;
}

bool is_full_screen_supported(void)
{
	return false;
}

bool is_full_screen_mode(void)
{
	return false;
}

void enter_full_screen_mode(void)
{
	/* stub */
}

void leave_full_screen_mode(void)
{
	/* stub */
}

const char *get_system_locale(void)
{
	int lang_code;

	lang_code = EM_ASM_INT({
		if (window.navigator.language.startsWith("ja"))
			return 0;
		return 1;
	});

	if (lang_code == 0)
		return "ja";

	return "en";
}

void finish_frame_io(void)
{
	opengl_start_rendering();
}

void speak_text(const char *text)
{
	UNUSED_PARAMETER(text);
}

void set_continuous_swipe_enabled(bool is_enabled)
{
	is_continuous_swipe_enabled = is_enabled;
}

/*
 * File I/O implementation for Browser's File System API
 */

/* Path length */
#define PATH_SIZE	(1024)

/* File read stream */
struct rfile {
	char *data;
	uint64_t size;
	uint64_t pos;
};

/* File write stream */
struct wfile {
	char *buf;
	uint64_t buf_size;
	uint64_t size;
};

/* Forward Declaration */
static void ungetc_rfile(struct rfile *rf, char c);

/*
 * Initialize the file system.
 */
bool init_file(void)
{
	return true;
}

/*
 * Cleanup the file system.
 */
void cleanup_file(void)
{
}

/* JS: Get a file size. */
EM_ASYNC_JS(int, onvlGetFileSize, (const char *dir_name, const char *file_name),
{
	/* TODO: 'save' is not supported. */
	const dirName = UTF8ToString(dir_name);
	if (dirName === 'save')
		return -1;

	/* Process recursively */
	const fileName = UTF8ToString(file_name);
	try {
		if (dirName === "") {
			const fileHandle = await dirHandle.getFileHandle(fileName, { create: false });
			const file = await fileHandle.getFile();
			return file.size;
		} else {
			const fullFileName = dirName + '/' + fileName;
			const fileNameSplit = fullFileName.split('/');
			var subdirHandle = dirHandle;
			for (i = 0; i < fileNameSplit.length - 1; i++) {
				subdirHandle = await subdirHandle.getDirectoryHandle(fileNameSplit[i], { create: false });
			}
			const fileHandle = await subdirHandle.getFileHandle(fileNameSplit[fileNameSplit.length - 1], { create: false });
			const file = await fileHandle.getFile();
			return file.size;
		}
	} catch(e) {
	}
	return -1;
});

/* JS: Get an entire file content. */
EM_ASYNC_JS(int, onvlReadFile, (const char *dir_name, const char *file_name, char *data),
{
	/* TODO: 'save' is not supported. */
	const dirName = UTF8ToString(dir_name);
	if (dirName === 'save')
		return -1;

	/* Process recursively */
	const fileName = UTF8ToString(file_name);
	try {
		if (dirName === "") {
			const fileHandle = await dirHandle.getFileHandle(fileName, { create: false });
			const file = await fileHandle.getFile();
			const fileSize = file.size;
			const fileReader = new FileReader();
			const arrayBuffer = await new Promise((resolve, reject) => {
					fileReader.addEventListener('load', () => resolve(fileReader.result));
					fileReader.readAsArrayBuffer(file);
				});
			const u8Array = new Uint8Array(arrayBuffer);
			writeArrayToMemory(u8Array, data);
			return 0;
		} else {
			const fullFileName = dirName + '/' + fileName;
			const fileNameSplit = fullFileName.split('/');
			var subdirHandle = dirHandle;
			for (i = 0; i < fileNameSplit.length - 1; i++) {
				subdirHandle = await subdirHandle.getDirectoryHandle(fileNameSplit[i], { create: false });
			}
			const fileHandle = await subdirHandle.getFileHandle(fileNameSplit[fileNameSplit.length - 1], { create: false });
			const file = await fileHandle.getFile();
			const fileSize = file.size;
			const fileReader = new FileReader();
			const arrayBuffer = await new Promise((resolve, reject) => {
					fileReader.addEventListener('load', () => resolve(fileReader.result));
					fileReader.readAsArrayBuffer(file);
				});
			const u8Array = new Uint8Array(arrayBuffer);
			writeArrayToMemory(u8Array, data);
			return 0;
		}
	} catch(e) {
		alert('onvlReadFile(): error ' + e);
	}
	return -1;
});

/*
 * Check if file exists.
 */
bool check_file_exist(const char *dir, const char *file)
{
	uint64_t size;

	/* Get a file size. */
	size = onvlGetFileSize(dir, file);
	if (size == -1) {
		/* Not found. */
		return false;
	}

	/* File exists. */
	return true;
}

/*
 * Open a file reader stream.
 */
struct rfile *open_rfile(const char *dir, const char *file, bool save_data)
{
	struct rfile *rf;
	uint64_t size;
	int result;

	/* Get a file size. */
	size = onvlGetFileSize(dir, file);
	if (size == -1) {
		if (!save_data)
			log_dir_file_open(dir, file);
		return NULL;
	}

	/* Allocate a rfile struct. */
	rf = malloc(sizeof(struct rfile));
	if (rf == NULL) {
		log_memory();
		return NULL;
	}
	rf->size = size;
	rf->pos = 0;
	if (size == 0) {
		rf->data = NULL;
		return rf;
	}

	/* Allocate a file buffer. */
	rf->data = malloc(size);
	if (rf->data == NULL) {
		log_memory();
		return NULL;
	}
	memset(rf->data, 0, size);

	/* Get an entire file content. */
	result = onvlReadFile(dir, file, rf->data);
	if (result == -1) {
		log_error("ASM ERROR.");
		free(rf);
		return NULL;
	}

	return rf;
}

/*
 * Get a file size.
 */
size_t get_rfile_size(struct rfile *rf)
{
	return rf->size;
}

/*
 * Read bytes from a file reader stream.
 */
size_t read_rfile(struct rfile *rf, void *buf, size_t size)
{
	if (rf->pos + size > rf->size)
		size = (size_t)(rf->size - rf->pos);
	if (size == 0)
		return 0;
	memcpy(buf, rf->data + rf->pos, size);
	rf->pos += size;
	return size;
}

/* Push back a character to a file reader stream. */
static void ungetc_rfile(struct rfile *rf, char c)
{
	/* HINT: c is not pushed back. */
	assert(rf->pos != 0);
	rf->pos--;
}

/*
 * Read a line from a file reader stream.
 */
const char *gets_rfile(struct rfile *rf, char *buf, size_t size)
{
	char *ptr;
	size_t len;
	char c;

	ptr = (char *)buf;

	for (len = 0; len < size - 1; len++) {
		if (read_rfile(rf, &c, 1) != 1) {
			*ptr = '\0';
			return len == 0 ? NULL : buf;
		}
		if (c == '\n' || c == '\0') {
			*ptr = '\0';
			return buf;
		}
		if (c == '\r') {
			if (read_rfile(rf, &c, 1) != 1) {
				*ptr = '\0';
				return buf;
			}
			if (c == '\n') {
				*ptr = '\0';
				return buf;
			}
			ungetc_rfile(rf, c);
			*ptr = '\0';
			return buf;
		}
		*ptr++ = c;
	}
	*ptr = '\0';
	return buf;
}

/*
 * Close a file reader stream.
 */
void close_rfile(struct rfile *rf)
{
	assert(rf != NULL);

	free(rf->data);
	free(rf);
}

/*
 * Go back to the top of a file stream.
 */
void rewind_rfile(struct rfile *rf)
{
	rf->pos = 0;
}

/*
 * Open a file writer stream.
 */
struct wfile *open_wfile(const char *dir, const char *file)
{
	/* TODO */
	return NULL;
}

/*
 * Write to a file writer stream.
 */
size_t write_wfile(struct wfile *wf, const void *buf, size_t size)
{
	/* TODO */
	return 0;
}

/*
 * Close a file writer stream.
 */
void close_wfile(struct wfile *wf)
{
	/* TODO */
}

/*
 * Remove a file.
 */
void remove_file(const char *dir, const char *file)
{
	/* TODO */
}
