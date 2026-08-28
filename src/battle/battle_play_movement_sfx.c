#include "fft/battle.h"

extern void main_play_sound_find_channel(s32);

void battle_play_movement_sfx(battle_display_unit_t* unit, s32 sound_id) {
    if ((unit->movement.word & 0x02000000) == 0) {
        main_play_sound_find_channel(sound_id);
    }
}
