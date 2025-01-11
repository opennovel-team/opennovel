/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

#define DRAW_IMAGE_FAST		draw_image_fast_avx
#define DRAW_IMAGE_EMOJI	draw_image_emoji_avx
#define DRAW_IMAGE_ADD		draw_image_add_avx
#define DRAW_IMAGE_DIM		draw_image_dim_avx
#define DRAW_IMAGE_RULE		draw_image_rule_avx
#define DRAW_IMAGE_MELT		draw_image_melt_avx
#define DRAW_IMAGE_SCALE	draw_image_scale_avx

#include "function.h"
