#include <iostream>

#include "configuration.hpp"
#include "window.hpp"

int
main(void)
{
    window::InitWindow();
    rl::SetTargetFPS(60);

    if (FORCE_FULLSCREEN)
        rl::ToggleFullscreen();

    while (! rl::WindowShouldClose())
    {
        if (! FORCE_FULLSCREEN)
            window::ResizeWindow();

        rl::BeginDrawing();

        {
            rl::ClearBackground(WHITE);
        }

        rl::EndDrawing();
    }

  rl::CloseWindow();

  return 0;
}
