/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

#define DRAW_IMAGE_FAST		draw_image_fast_avx2
#define DRAW_IMAGE_EMOJI	draw_image_emoji_avx2
#define DRAW_IMAGE_ADD		draw_image_add_avx2
#define DRAW_IMAGE_DIM		draw_image_dim_avx2
#define DRAW_IMAGE_RULE		draw_image_rule_avx2
#define DRAW_IMAGE_MELT		draw_image_melt_avx2
#define DRAW_IMAGE_SCALE	draw_image_scale_avx2

#include "function.h"
