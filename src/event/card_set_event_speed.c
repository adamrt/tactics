#include "psx/types.h"

extern s8 g_card_event_speed;
extern void set_event_speed(s32 speed);

void card_set_event_speed(s32 speed) {
    g_card_event_speed = speed;
    if (speed == 0) {
        speed = 1;
    }
    set_event_speed(speed);
}
