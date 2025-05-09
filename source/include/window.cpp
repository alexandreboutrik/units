#include "window.hpp"

#include "assets.hpp"

namespace window {

extern void
InitWindow()
{
    int cur_mon = rl::GetCurrentMonitor();

    rl::InitWindow(rl::GetMonitorWidth(cur_mon), rl::GetMonitorHeight(cur_mon), WINDOW_TITLE);

    /* Centralize the window */
    window::ResizeWindow(true);
}

extern void
ResizeWindow(const bool centralize)
{
    int cur_mon = rl::GetCurrentMonitor();

    int mon_width  = rl::GetMonitorWidth(cur_mon);
    int mon_height = rl::GetMonitorHeight(cur_mon);

    int w_width  = SCALING_WINDOWED * mon_width;
    int w_height = SCALING_WINDOWED * mon_height;

    if (centralize)
    {
        int pos_x = (mon_width  - w_width) / 2;
        int pos_y = (mon_height - w_height) / 2;

        rl::SetWindowPosition(pos_x, pos_y);
    }

    rl::SetWindowSize(w_width, w_height);
}

extern void
DrawText(
    const std::string& fontName, const std::string& text,
    const float pos_x, const float pos_y, Color tint)
{
    auto [font, fontSize] = assets::Manager::Get().GetFontData(fontName);

    rl::DrawTextEx(font, text.c_str(), Vector2{ pos_x, pos_y }, fontSize, 0, tint);
}

extern void
DrawImage(const std::string& name, const int pos_x, const int pos_y)
{
    assets::Manager::Get().DrawImage(name, pos_x, pos_y);
}

} /* window namespace */
