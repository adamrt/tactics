#include "psx/types.h"

extern u8 D_8013A608;
extern s32 g_world_sound_effect_id_to_play;

void world_set_sound_effect_to_confirm_checked(void) {
    if (D_8013A608 == 0) {
        g_world_sound_effect_id_to_play = 1;
    }
}
