#pragma once

#include <string>

#include "configuration.hpp"

namespace window {

/* Initialize the application window */
extern void InitWindow();

/*
 * Resize the window based on a scaling factor (see window.cpp).
 *
 * @param centralize reset/centralize the window position
 */
extern void ResizeWindow(const bool centralize = false);

/*
 * DrawText wrapper with automatic font and fontSize lookup by [fontName].
 *
 * @param fontName      font identifier
 * @param text          text string to render
 * @param pos_{x,y}     left and top origin
 * @param tint          text foreground color (RGBA format)
 * @throws std::runtime_error if [fontName] is not found
 */
extern void DrawText(
    const std::string& fontName, const std::string& text,
    const float pos_x, const float pos_y, Color tint);

/*
 * DrawImage wrapper. Same as assets::Manager::Get().DrawImage(...).
 *
 * @param name          image identifier
 * @param pos_{x,y}     left and top origin
 * @throws std::runtime_error if [name] is not found
 */
extern void DrawImage(
    const std::string& name, const int pos_x, const int pos_y);

} /* window namespace */
