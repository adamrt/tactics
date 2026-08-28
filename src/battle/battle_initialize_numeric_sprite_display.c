#include "fft/battle.h"

extern u8 g_battle_numeric_sprite_display_0[];
extern u8 g_battle_numeric_sprite_display_1[];
extern u8 g_battle_numeric_sprite_display_2[];

battle_sprite_display_data_t* battle_initialize_numeric_sprite_display(
    s32 unit_index, s32 display_section, battle_sprite_display_data_t* default_display) {
    battle_sprite_display_data_t* display;
    battle_sprite_part_display_data_t* part;
    /* Pin: the target keeps the loop counter in the dead $a0 (unit_index);
     * unpinned GCC picks $v1 and swaps it with the part pointer. */
    register s32 count __asm__("$4");

    display = default_display;
    switch (display_section) {
    case 0:
        display = (battle_sprite_display_data_t*)&g_battle_numeric_sprite_display_0[unit_index * 0x440];
        break;
    case 1:
        display = (battle_sprite_display_data_t*)&g_battle_numeric_sprite_display_1[unit_index * 0x440];
        break;
    case 2:
        display = (battle_sprite_display_data_t*)&g_battle_numeric_sprite_display_2[unit_index * 0x440];
        break;
    default:
        count = 0;
        goto initialize;
    }

    /* Initialised on both paths (not before the switch) so the zero lands
     * in each arm's jump delay slot and the loop is not reversed. */
    count = 0;
initialize:
    /* The target walks the part records from the slot base (parts[0] sits
     * two record-sizes in), so index by 2 rather than starting at ->parts. */
    part = (battle_sprite_part_display_data_t*)display;
    display->blue = 0x80;
    display->green = 0x80;
    display->red = 0x80;
    do {
        part[2].flags = 0;
        count++;
        part++;
    } while (count <= 0);
    display->part_count = 0;
    return display;
}
