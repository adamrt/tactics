#include "psx/types.h"

extern u8* g_last_unit_misc_data;
extern void battle_store_unit_animation_facing(u32 animation, s16 facing, u8* unit);

void battle_store_unknown_facing_for_all_units(u32 animation) {
    u8* unit = g_last_unit_misc_data;

    while (unit != 0) {
        battle_store_unit_animation_facing(animation, *(s16*)(unit + 0x6c), unit);
        unit = *(u8**)unit;
    }
}
