#include "fft/battle.h"

extern void battle_configure_misc_unit_palette_modulation_1f(s32 unit_id);
extern s32 func_80081C60(s32 sprite_id);
extern u8* battle_get_spritesheet_shp_data_address(u32 index);
extern u8* battle_get_spritesheet_seq_data_address(u32 index);
extern u8* battle_get_tile_data_pointer(s32 x, s32 y, s32 z);
extern void battle_check_for_tile_status_palette_mod(battle_misc_data_t* unit, s32 status, s32 flag);
extern void battle_store_unit_animation_facing_movement_data(u32 animation, s16 facing, u8* unit);
extern void battle_some_kind_of_entd_unit_manipulation(battle_stats_t* stats);
extern void func_80199EC8(s32 arg0);

void battle_poach_morbol_transformation(battle_misc_data_t* unit) {
    u32 flags;
    u8* tile;

    flags = unit->status_flags_5_6;
    if ((flags & 0x180) == 0) {
        return;
    }
    if (flags & 0x80) {
        unit->status_flags_5_6 = flags & ~0x80;
        battle_configure_misc_unit_palette_modulation_1f(unit->unit_id);
        return;
    }
    if ((flags & 0x100) == 0) {
        return;
    }
    unit->status_flags_5_6 = flags & ~0x100;
    unit->special_graphic_y_offset = 0;
    unit->spritesheet_id = 0x92;
    unit->spritesheet_vram_slot = func_80081C60(0x92);
    unit->shp_data = battle_get_spritesheet_shp_data_address(0x92);
    unit->seq_data = battle_get_spritesheet_seq_data_address(0x92);
    unit->stored_palette = 0;
    unit->vram_spritesheet_id = unit->spritesheet_vram_slot + 0x14;
    tile = battle_get_tile_data_pointer(unit->map_x, unit->map_y, unit->map_z);
    battle_check_for_tile_status_palette_mod(unit, (tile[6] >> 2) & 3, 1);
    battle_store_unit_animation_facing_movement_data(3, unit->facing, (u8*)unit);
    battle_some_kind_of_entd_unit_manipulation(unit->battle_data);
    func_80199EC8(unit->battle_data->misc_unit_id);
}
