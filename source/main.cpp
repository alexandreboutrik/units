#include <iostream>

#include "assets.hpp"
#include "configuration.hpp"
#include "window.hpp"

/*
 * UNITS
 *  A practical unit conversion tool focused on Civil Engineering needs.
 *  Developed for UTFPR-TD's Research Methodology course.
 *
 * @return Exit status (0 on success)
 */
int
main(void)
{
    window::InitWindow();
    rl::SetTargetFPS(60);

    /* Full screen mode */
    if (FORCE_FULLSCREEN)
        rl::ToggleFullscreen();

    /* Main application loop */
    while (! rl::WindowShouldClose())
    {
        /*
         * In windowed mode, enforce fixed window size by continuously
         * resetting to configured dimensions (see window.cpp).
         * This effectively prevents user resizing despite window manager
         * requests.
         */
        if (! FORCE_FULLSCREEN)
            window::ResizeWindow();

        rl::BeginDrawing();
        rl::ClearBackground(BACKGROUND_COLOR);

        {
            /*
             * TEMPORARY: Test DrawImage and DrawText rendering
             */
            assets::Manager::Get().DrawImage("logo", 10, 10);
            DrawTextEx(MAIN_FONT_64, "Agave Font",
                Vector2{ 200, 200 }, 64, 0, BLACK);
            DrawText("Raylib Font", 200, 300, 64, BLACK);
            DrawTextEx(assets::Manager::Get().GetFont("liberation-sans"),
                "Liberation Sans Font", Vector2{ 200, 400 }, 64, 0, BLACK);
            DrawTextEx(assets::Manager::Get().GetFont("marcha"),
                "Marcha Font", Vector2{ 200, 500 }, 64, 0, BLACK);
        }

        rl::EndDrawing();
    }

  rl::CloseWindow();

  return 0;
}
