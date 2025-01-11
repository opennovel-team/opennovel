/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

#include "../opennovel.h"

bool is_avx2_available;
bool is_avx_available;
bool is_sse42_available;
bool is_sse4_available;
bool is_sse3_available;
bool is_sse2_available;
bool is_sse_available;

void check_cpuid(void)
{
	is_avx2_available = __builtin_cpu_supports("avx2");
	is_avx_available = __builtin_cpu_supports("avx");
	is_sse42_available = __builtin_cpu_supports("sse4.2");
	is_sse4_available = __builtin_cpu_supports("sse4.1");
	is_sse3_available = __builtin_cpu_supports("sse3");
	is_sse2_available = __builtin_cpu_supports("sse2");
	is_sse_available = __builtin_cpu_supports("sse");
}
