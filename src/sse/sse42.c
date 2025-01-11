/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

#define DRAW_IMAGE_FAST		draw_image_fast_sse42
#define DRAW_IMAGE_EMOJI	draw_image_emoji_sse42
#define DRAW_IMAGE_ADD		draw_image_add_sse42
#define DRAW_IMAGE_DIM		draw_image_dim_sse42
#define DRAW_IMAGE_RULE		draw_image_rule_sse42
#define DRAW_IMAGE_MELT		draw_image_melt_sse42
#define DRAW_IMAGE_SCALE	draw_image_scale_sse42

#include "function.h"
