/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

/*
 * This header handles non-C89 and/or compiler-specific features.
 *
 * - The compilers we support as of April 2024 are:
 *   - GCC 13 or later
 *   - LLVM/Clang 15 or later
 *   - MSVC 14 or later
 */

#ifndef OPENNOVEL_TYPES_H
#define OPENNOVEL_TYPES_H

/*
 * Define macros that indicate a target platform we are compiling to.
 *  - OPENNOVEL_TARGET_WIN32   for Win32 (x86/x64/Arm64)
 *  - OPENNOVEL_TARGET_MACOS   for macOS (Arm64/x86_64)
 *  - OPENNOVEL_TARGET_IOS     for iOS (Arm64)
 *  - OPENNOVEL_TARGET_ANDROID for Android (armv8/armv7/x86_64)
 *  - OPENNOVEL_TARGET_WASM    for Wasm with Emscripten
 *  - OPENNOVEL_TARGET_POSIX   for Linux, *BSD, and Unix
 */
#if defined(_WIN32)
#define OPENNOVEL_TARGET_WIN32
#elif defined(__linux) && !defined(__ANDROID__)
#define OPENNOVEL_TARGET_POSIX
#elif defined(__FreeBSD__)
#define OPENNOVEL_TARGET_POSIX
#elif defined(__NetBSD__)
#define OPENNOVEL_TARGET_POSIX
#elif defined(__OpenBSD__)
#define OPENNOVEL_TARGET_POSIX
#elif defined(__sun)
#define OPENNOVEL_TARGET_POSIX
#elif defined(__ANDROID__)
#define OPENNOVEL_TARGET_ANDROID
#elif defined(__EMSCRIPTEN__)
#define OPENNOVEL_TARGET_WASM
#elif defined(USE_UNITY)
#define OPENNOVEL_TARGET_UNITY
#elif defined(__APPLE__) && __has_include(<TargetConditionals.h>)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define OPENNOVEL_TARGET_IOS
#else
#define OPENNOVEL_TARGET_MACOS
#endif
#else
#error "No target detected."
#endif

/*
 * For GCC
 */
#if defined(__GNUC__) && !defined(__llvm__)

/* Define a macro that indicates a target architecture. */
#if defined(__i386__) && !defined(__x86_64__)
#define OPENNOVEL_ARCH_X86
#elif defined(__x86_64__)
#define OPENNOVEL_ARCH_X86_64
#elif defined(__arm__)
#define OPENNOVEL_ARCH_ARM32
#elif defined(__aarch64__)
#define OPENNOVEL_ARCH_ARM64
#endif

/* Struct member definition with 512-bit memory alignment. */
#define SIMD_ALIGNED_MEMBER(cdecl) cdecl __attribute__((aligned(64)))

/* uint*_t and int*_t */
#include <stdint.h>

/* bool */
#ifndef __cplusplus
#include <stdbool.h>
#endif

/* Inline function. */
#define INLINE				__inline

/* No pointer aliasing. */
#define RESTRICT			__restrict

/* Suppress unused warnings. */
#define UNUSED_PARAMETER(x)		(void)(x)

/* UTF-8 string literal. */
#define U8(s)				u8##s

/* UTF-32 character literal. */
#define U32_C(literal, unicode)		U##literal

#endif /* End of GCC */

/*
 * For Clang/LLVM
 */
#if defined(__llvm__)

#if defined(__i386__) && !defined(__x86_64__)
#define OPENNOVEL_ARCH_X86
#elif defined(__x86_64__)
#define OPENNOVEL_ARCH_X86_64
#elif defined(__arm__)
#define OPENNOVEL_ARCH_ARM32
#elif defined(__aarch64__)
#define OPENNOVEL_ARCH_ARM64
#endif

#define SIMD_ALIGNED_MEMBER(cdecl) cdecl __attribute__((aligned(64)))

#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#define INLINE				__inline
#define RESTRICT			__restrict
#define UNUSED_PARAMETER(x)		(void)(x)
#define U8(s)				u8##s
#define U32_C(literal, unicode)		U##literal

#endif /* End of Clang/LLVM */

/*
 * For MSVC
 */
#ifdef _MSC_VER

#if defined(_M_IX86)
#define OPENNOVEL_ARCH_X86
#elif defined(_M_X64)
#define OPENNOVEL_ARCH_X86_64
#elif defined(_M_ARM64)
#define OPENNOVEL_ARCH_ARM64
#endif

#define SIMD_ALIGNED_MEMBER(cdecl) __declspec(align(64)) cdecl

/* Do not get warnings for usages of string.h functions. */
#define _CRT_SECURE_NO_WARNINGS

/* POSIX libc to MSVCRT mapping */
#define strdup _strdup
#define strcasecmp _stricmp

#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#define INLINE				__inline
#define RESTRICT			__restrict
#define UNUSED_PARAMETER(x)		(void)(x)
#define U8(s)				u8##s
#define U32_C(literal, unicode)		U##literal

#endif /* End of MSVC */

/*
 * For Sun Studio
 */
#ifdef __sun

#if defined(__sparc)
#define OPENNOVEL_ARCH_SPARC
#else
#define OPENNOVEL_ARCH_X86_64
#endif

#define SIMD_ALIGNED_MEMBER(cdecl) cdecl

#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#define INLINE				__inline
#define RESTRICT			__restrict
#define UNUSED_PARAMETER(x)		(void)(x)
#define U8(s)				u8##s
#define U32_C(literal, unicode)		(unicode)

#endif /* End of Sun Studio */

#endif
