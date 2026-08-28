#include "psx/types.h"

extern s8 g_bunit_event_speed;
extern void set_event_speed(s32 speed);

void bunit_set_event_speed(s32 speed) {
    g_bunit_event_speed = speed;
    if (speed == 0) {
        speed = 1;
    }
    set_event_speed(speed);
}
