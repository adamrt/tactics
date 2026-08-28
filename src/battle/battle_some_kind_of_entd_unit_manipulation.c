#include "fft/battle.h"

extern void main_copy_byte_data(u8* dst, u8* src, s32 len);
extern void initialize_unit_battle_data(battle_stats_t* unit, s32 arg1, s32 arg2,
    s32 arg3);
extern void main_calculate_unit_palette_spritesheet(battle_stats_t* unit, u8* out);

void battle_some_kind_of_entd_unit_manipulation(battle_stats_t* unit) {
    u8 saved[0x10];
    u8 sp20[8];
    u8* ability_block;
    u8 unit_id;
    u8 formation_index;
    /* Pins: GCC wants these two saved bytes in $s3/$s4 the other way round
     * regardless of declaration or statement order (see cookbook). */
    register u8 x __asm__("$19");
    register u8 position_low __asm__("$20");
    u32 position;
    s32 higher_elevation;
    s32 facing;

    /* 0x12c..0x13b: the tail of learned_abilities, saved across the reset. */
    ability_block = &unit->learned_abilities[0x12c - 0x99];
    unit_id = unit->unit_id;
    unit->job_id = 0x82;
    unit->character_identity = 0x82;
    main_copy_byte_data(ability_block, saved, 0x10);
    formation_index = unit->formation_index;
    position = unit->position.raw;
    x = unit->x;
    position_low = *(u8*)&unit->position;
    unit->formation_index = 0xFE;
    higher_elevation = position >> 15;
    facing = (position >> 8) & 0xF;
    initialize_unit_battle_data(unit, 0, 0, 0x82);
    *(u8*)&unit->position = position_low;
    unit->x = x;
    unit->formation_index = formation_index;
    unit->position.raw = (((unit->position.raw & 0x7FFF) | (higher_elevation << 15)) & 0xF0FF) | (facing << 8);
    main_copy_byte_data(saved, ability_block, 0x10);
    unit->unit_id = unit_id;
    main_calculate_unit_palette_spritesheet(unit, sp20);
}
