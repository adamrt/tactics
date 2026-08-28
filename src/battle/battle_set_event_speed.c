#include "psx/types.h"

extern s32 g_event_speed;
extern void battle_set_animation_speed(void);

void battle_set_event_speed(s32 speed) {
    g_event_speed = speed;
    battle_set_animation_speed();
}
