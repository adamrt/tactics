#include "psx/types.h"

extern s32 g_world_sound_effect_id_to_play;

void world_set_sound_effect_to_confirm(void) {
    g_world_sound_effect_id_to_play = 1;
}
