#include "fft/battle.h"

extern void main_set_svector(s16* vector, s32 x, s32 y, s32 z);

void battle_initialize_position_vector_copies(battle_misc_data_t* unit) {
    s32 offset;
    s32 i;

    unit->_unknown_2e8 = 1;
    i = 0;
    /* The retail loop walks display_svectors by an integer offset
     * (li 0x2ec / addiu 8); a typed battle_svector_t pointer emits addiu from unit. */
    offset = 0x2ec;
    do {
        main_set_svector((s16*)((u8*)unit + offset), unit->screen_x, unit->screen_z, unit->screen_y);
        offset += 8;
        i++;
    } while (i < 6);
}
