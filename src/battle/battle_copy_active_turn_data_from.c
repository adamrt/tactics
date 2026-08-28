#include "psx/types.h"

extern u8 g_battle_active_turn_banner[];
extern u8 g_battle_active_turn_unit[];
extern u8 g_battle_billboard_data[];
extern void world_copy_bytes(u8* destination, const u8* source, s32 count);

void battle_copy_active_turn_data_from(const u8* banner,
    const u8* unit,
    const u8* billboard) {
    world_copy_bytes(g_battle_active_turn_banner, banner, 0x22);
    world_copy_bytes(g_battle_active_turn_unit, unit, 0x0e);
    world_copy_bytes(g_battle_billboard_data, billboard, 0x40);
}
