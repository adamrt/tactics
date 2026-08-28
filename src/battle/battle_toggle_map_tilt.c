#include "psx/types.h"

extern void main_play_sound(s32 sound_id, s32 arg);
extern s32 g_battle_map_tilt_action;
extern s32 g_battle_map_tilt_target;
extern s32 g_battle_map_tilt_increment;

/* The retail routine preserves the ambient a1 value on the state-1 path. */
void battle_toggle_map_tilt(s32 unused_0, s32 sound_arg) {
    s32 target;
    s32 one;
    s32 value;

    target = g_battle_map_tilt_target;
    one = 1;

    if (target == one) {
        value = 2;
        goto set_action;
    }
    sound_arg = 2;
    if (target == sound_arg) {
        g_battle_map_tilt_target = one;
        g_battle_map_tilt_action = 4;
    } else {
        value = 3;
        if (target == value) {
            value = 4;
        set_action:
            g_battle_map_tilt_action = value;
            g_battle_map_tilt_target = value;
        } else {
            value = 4;
            if (target == value) {
                g_battle_map_tilt_target = one;
                g_battle_map_tilt_action = 2;
            }
        }
    }
    g_battle_map_tilt_increment = 1;
    main_play_sound(0x31, sound_arg);
}
