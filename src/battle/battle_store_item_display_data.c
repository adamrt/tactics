#include "fft/battle.h"

typedef struct ItemGraphicData {
    u8 _pad0[0xc];
    u8 x_load_location;
    u8 y_load_location;
    u16 clut;
    s16 width;
    s16 height;
} ItemGraphicData;

extern void get_item_graphic_data(ItemGraphicData* output, u32 item_id);
extern void battle_store_sprite_display_data(battle_sprite_display_data_t* display, s32 graphic_index,
    s16 x_offset, s16 y_offset, u8 x_load_location,
    u8 y_load_location, s16 width, s16 height, s32 flags);

void battle_store_item_display_data(battle_render_unit_t* unit, u32 item_id) {
    ItemGraphicData data;

    get_item_graphic_data(&data, item_id);
    unit->found_item_display->clut = data.clut;
    battle_store_sprite_display_data(unit->found_item_display, 0, (16 - data.width) / 2 - 8,
        (16 - data.height) / 2 - 8, data.x_load_location,
        data.y_load_location, data.width, data.height, 0);
}
