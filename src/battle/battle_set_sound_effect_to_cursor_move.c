#include "psx/types.h"

extern s32 g_sound_effect_id_to_play;

void battle_set_sound_effect_to_cursor_move(void) {
    g_sound_effect_id_to_play = 3;
}
