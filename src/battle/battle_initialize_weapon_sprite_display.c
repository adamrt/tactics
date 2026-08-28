#include "fft/battle.h"

extern u8 g_battle_weapon_sprite_display_data[];

battle_sprite_display_data_t* battle_initialize_weapon_sprite_display(s32 unit_index,
    s32 display_type) {
    s32 weapon_part;
    u8* record;
    battle_sprite_display_data_t* display;
    volatile battle_sprite_part_display_data_t* part;

    weapon_part = 2;
    record = g_battle_weapon_sprite_display_data + unit_index * 0x440;
    display = (battle_sprite_display_data_t*)(record + display_type * 0x24);
    part = (volatile battle_sprite_part_display_data_t*)display->parts;
    display->blue = 0x80;
    display->green = 0x80;
    display->red = 0x80;
    do {
        part[2].flags = 0;
        weapon_part--;
        part--;
    } while (weapon_part >= 0);
    display->part_count = 0;
    return display;
}
