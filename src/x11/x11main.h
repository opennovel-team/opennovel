/* -*- tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

#ifndef OPENNOVEL_X11_X11MAIN_H
#define OPENNOVEL_X11_X11MAIN_H

/* Color Format */
#define DEPTH		(24)
#define BPP		(32)

extern Display *display;
extern Window window;

extern bool init_x11_graphics(void);
extern void cleanup_x11_graphics(void);
extern void start_x11_rendering(void);
extern void end_x11_rendering(void);

#endif
