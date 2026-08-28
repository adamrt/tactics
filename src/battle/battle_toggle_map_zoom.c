#include "psx/types.h"

extern void main_play_sound(s32 sound_id, s32 arg1);
extern s32 g_battle_map_zoom_action;
extern s32 g_battle_map_zoom_target;
extern s32 g_battle_map_zoom_increment;

/* Toggle the battle map zoom between "in" (target=1, action=2) and
   "out" (target=4, action=4), playing the corresponding zoom SFX. Any
   other current zoom target is left alone. */
void battle_toggle_map_zoom(void) {
    s32 sound_id;
    s32 zoomed_in = 1;

    if (g_battle_map_zoom_target == zoomed_in) {
        g_battle_map_zoom_action = 4;
        g_battle_map_zoom_target = 4;
        sound_id = 0x11;
        goto play;
    }
    sound_id = 0xE;
    if (g_battle_map_zoom_target == 4) {
        g_battle_map_zoom_target = zoomed_in;
        g_battle_map_zoom_action = 2;
    play:
        main_play_sound(sound_id, zoomed_in);
    }
    g_battle_map_zoom_increment = 4;
}
