#include "fft/battle.h"

typedef struct UnitGraphicsLoadDescriptor {
    u8 map_x;
    u8 map_y;
    u8 map_level;
    u8 _pad003;
    u16 map_height;
    s16 portrait_id;
    u16 palette_id;
    u16 misc_id;
    battle_stats_t* battle_stats;
    u32 flags;
} UnitGraphicsLoadDescriptor;

extern volatile s32 g_unit_graphics_load_count;
extern UnitGraphicsLoadDescriptor g_unit_graphics_load_descriptors[];

void battle_append_unit_graphics_load_descriptor(
    u8 map_x, u8 map_y, u8 map_level, u16 map_height, s32 portrait_id,
    u16 palette_id, u16 misc_id, battle_stats_t* battle_stats, u32 flags) {
    volatile s32* load_count = &g_unit_graphics_load_count;
    s32 count;

    g_unit_graphics_load_descriptors[*load_count].map_x = map_x;
    g_unit_graphics_load_descriptors[*load_count].map_y = map_y;
    g_unit_graphics_load_descriptors[*load_count].map_level = map_level;
    g_unit_graphics_load_descriptors[*load_count].map_height = map_height;
    g_unit_graphics_load_descriptors[*load_count].portrait_id = portrait_id;
    if ((s16)portrait_id >= 0x9F) {
        g_unit_graphics_load_descriptors[*load_count].portrait_id = 1;
    }
    g_unit_graphics_load_descriptors[*load_count].palette_id = palette_id;
    g_unit_graphics_load_descriptors[*load_count].misc_id = misc_id;
    g_unit_graphics_load_descriptors[*load_count].battle_stats = battle_stats;
    g_unit_graphics_load_descriptors[*load_count].flags = flags;
    count = *load_count;
    if (count < 16) {
        *load_count = count + 1;
    }
}
