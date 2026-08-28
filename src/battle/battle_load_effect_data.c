#include "psx/types.h"

extern s16 g_ability_effect_id;
extern void battle_load_effect_lba_and_size(s32, s32*, s32*);
extern void main_load_data_from_disc(s32, s32, void*);

void battle_load_effect_data(void) {
    s32 lba;
    s32 byte_length;

    battle_load_effect_lba_and_size(g_ability_effect_id, &lba, &byte_length);
    if (byte_length == 0) {
        g_ability_effect_id = 1;
        battle_load_effect_lba_and_size(1, &lba, &byte_length);
    }
    main_load_data_from_disc(lba, byte_length, 0);
}
