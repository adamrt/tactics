#include "psx/types.h"

extern s8 g_bunit_event_speed;

s32 bunit_get_event_speed(void) {
    s32 speed;

    speed = g_bunit_event_speed;
    if (speed == 0) {
        return 1;
    }
    return speed;
}
