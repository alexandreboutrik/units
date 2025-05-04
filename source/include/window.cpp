#include "window.hpp"

#include "configuration.hpp"

namespace window {

extern void
ResizeWindow()
{
    int cur_mon = rl::GetCurrentMonitor();

    int mon_width  = GetMonitorWidth(cur_mon);
    int mon_height = GetMonitorHeight(cur_mon);

    int w_width  = SCALING_WINDOWED * mon_width;
    int w_height = SCALING_WINDOWED * mon_height;

    int pos_x = (mon_width  - w_width) / 2;
    int pos_y = (mon_height - w_height) / 2;

    rl::SetWindowPosition(pos_x, pos_y);
    rl::SetWindowSize(w_width, w_height);
}

} /* window namespace */
