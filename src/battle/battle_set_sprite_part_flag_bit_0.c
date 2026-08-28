#include "fft/battle.h"

void battle_set_sprite_part_flag_bit_0(battle_sprite_display_data_t* display,
    s32 part_index, s32 enabled) {
    /* Pin: unpinned, GCC computes the record address in $v0 instead of $v1
     * (register swap only, same size). */
    register battle_sprite_part_display_data_t* part __asm__("$3");
    u8 flags;

    /* The target indexes the part records from the slot base (parts[0] sits
     * two record-sizes in), hence the +2. */
    if (enabled != 0) {
        part = (battle_sprite_part_display_data_t*)display + part_index;
        flags = part[2].flags | 1;
    } else {
        part = (battle_sprite_part_display_data_t*)display + part_index;
        flags = part[2].flags & 0xfe;
    }
    part[2].flags = flags;
}
