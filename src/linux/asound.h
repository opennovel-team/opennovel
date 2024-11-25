/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

#ifndef OPENNOVEL_ASOUND_H
#define OPENNOVEL_ASOUND_H

#include "../types.h"

/* Initialize ALSA. */
bool init_sound(void);

/* Cleanup ALSA. */
void cleanup_sound(void);

#endif
