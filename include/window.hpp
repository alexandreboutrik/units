#pragma once

#include <string>

#include "configuration.hpp"

namespace window {

extern  void    InitWindow();
extern  void    ResizeWindow();

extern  void    DrawText
                    (const std::string& name, const std::string& text,
                    const float pos_x, const float pos_y, Color tint);

} /* window namespace */
