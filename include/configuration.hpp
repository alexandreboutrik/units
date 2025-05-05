#pragma once

/*
 * This allows using Raylib functions with the 'rl::' prefix.
 * Define 'rl::' as a macro that expands to '::'.
 */
#include "raylib.h"
#define rl

#define     WINDOW_TITLE        "UNITS"
#define     FORCE_FULLSCREEN    false
#define     SCALING_WINDOWED    0.75

#define     BACKGROUND_COLOR    RAYWHITE

#define     MAIN_FONT_FILE      "AgaveNerdFont-Regular.ttf"

#ifndef ASSETS
#define ASSETS "."
#endif
