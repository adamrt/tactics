#include "fft/battle.h"

extern void save_3_u16(battle_svector_t* output, u16 x, u16 y, u16 z);
extern u32* main_get_otag(void);
extern void construct_polygon_data_for_units(battle_sprite_display_data_t* display, u32 graphics_count,
    s32 unused_a, battle_svector_t* position, s32 unused_b,
    s32 flags, battle_svector_t* zoom, u32* otag);

void battle_setup_item_get_rendering(battle_render_unit_t* unit) {
    battle_svector_t position;
    battle_svector_t zoom;
    u32* otag;

    if ((unit->sprite_flags & 2) != 0) {
        position.vx = (s16)(s8)((u8*)unit)[0x2d2];
    } else {
        position.vx = -(s16)(s8)((u8*)unit)[0x2d2];
    }
    position.vy = (s16)(s8)((u8*)unit)[0x2d3];
    position.vx += unit->camera_relative_position.vx;
    position.vy += unit->camera_relative_position.vy;
    save_3_u16(&zoom, 0x1000, 0x1000, 0x1000);
    otag = main_get_otag();
    otag += unit->otag_depth;
    construct_polygon_data_for_units(unit->found_item_display,
        unit->found_item_display->part_count, 0, &position, 0, 0,
        &zoom, otag);
}
