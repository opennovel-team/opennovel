/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * OpenNovel
 * Copyright (c) 2001-2024, OpenNovel.org. All rights reserved.
 */

/*
 * Main Header
 */

#ifndef OPENNOVEL_OPENNOVEL_H
#define OPENNOVEL_OPENNOVEL_H

 /* Compiler-specific features */
#include "types.h"

/* Standard C (ANSI-C/C89/C90) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <assert.h>

/* HAL (Hardware Abstraction Layer) */
#include "hal.h"

/* Subsystems */
#include "anime.h"	/* The animation subsystem */
#include "ciel.h"	/* The Ciel direction subsystem */
#include "conf.h"	/* The configuration subsystem */
#include "event.h"	/* The event handling subsystem */
#include "file.h"	/* The file subsystem */
#include "glyph.h"	/* The glyph rendering and text layout subsystem */
#include "gui.h"	/* The GUI subsystem */
#include "history.h"	/* The history subsystem */
#include "image.h"	/* The image subsystem */
#include "log.h"	/* The log subsystem */
#include "main.h"	/* The main subsystem */
#include "mixer.h"	/* The mixer subsystem */
#include "motion.h"	/* The motion subsystem */
#include "save.h"	/* The save subsystem */
#include "script.h"	/* The scenario script subsystem */
#include "seen.h"	/* The seen flag subsystem */
#include "stage.h"	/* The stage rendering subsystem */
#include "vars.h"	/* The variable subsystem */
#include "wave.h"	/* The sound stream subsystem */
#include "wms.h"	/* The WMS subsystem */
#if defined(USE_EDITOR)
#include "pro.h"	/* The editor extension */
#include "package.h"	/* The packager subsystem */
#endif

/*
 * Directory Names
 */

/* The name of the config file directory */
#define CONF_DIR		NULL

/* The name of the background image directory */
#define BG_DIR			"bg"

/* The name of the character image directory */
#define CH_DIR			"ch"

/* The name of the rule image directory */
#define RULE_DIR		"rule"

/* The name of the system image directory */
#define CG_DIR			"cg"

/* The name of the background music directory */
#define BGM_DIR			"bgm"

/* The name of the sound effect directory */
#define SE_DIR			"se"

/* The name of the voice directory */
#define CV_DIR			"cv"

/* The name of the font file directory */
#define FONT_DIR		"font"

/* The name of the scenario file directory */
#define SCENARIO_DIR		"txt"

/* The name of the GUI file directory */
#define GUI_DIR			"gui"

/* The name of the anime file directory */
#define ANIME_DIR		"anime"

/* The name of the WMS file directory */
#define WMS_DIR			"wms"

/* The name of the video file directory */
#define MOV_DIR			"mov"

/* The name of the save file directory */
#define SAVE_DIR		"sav"

/*
 * File Names
 */

/* The config file name. */
#define CONFIG_FILE		"project.txt"

/* The package file name. */
#define PACKAGE_FILE		"data01.arc"

/* The log file name. */
#define LOG_FILE		"log.txt"

/* The initial scenario file. */
#define INIT_FILE		"init.txt"

/* The system menu GUI file name. */
#define SYSMENU_GUI_FILE	"sysmenu.txt"

/* The save GUI file name. */
#define SAVE_GUI_FILE		"save.txt"

/* The load GUI file name. */
#define LOAD_GUI_FILE		"load.txt"

/* The history GUI file name. */
#define HISTORY_GUI_FILE	"history.txt"

/* The config GUI file name. */
#define CONFIG_GUI_FILE		"config.txt"

#endif
