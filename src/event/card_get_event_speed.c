#include "psx/types.h"

extern s8 g_card_event_speed;

s32 card_get_event_speed(void) {
    s32 speed;

    speed = g_card_event_speed;
    if (speed == 0) {
        return 1;
    }
    return speed;
}
