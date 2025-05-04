#include <iostream>

#include "configuration.hpp"
#include "window.hpp"

int
main(void)
{
    rl::InitWindow(16, 16, WINDOW_TITLE);
    rl::SetTargetFPS(60);

    while (! rl::WindowShouldClose())
    {
        if (FORCE_FULLSCREEN && (! rl::IsWindowFullscreen()))
            rl::ToggleFullscreen();
        else
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
