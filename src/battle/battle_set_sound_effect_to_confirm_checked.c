#include "psx/types.h"

extern u8 D_8014D324;
extern s32 g_sound_effect_id_to_play;

void battle_set_sound_effect_to_confirm_checked(void) {
    if (D_8014D324 == 0) {
        g_sound_effect_id_to_play = 1;
    }
}
