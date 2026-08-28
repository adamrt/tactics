#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void set_thrown_item_graphic_and_palette(u32 item_id,
    battle_misc_data_t* unit);

void battle_set_thrown_item_palette_by_misc_id(u32 item_id, u32 misc_id) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    if (unit != 0) {
        set_thrown_item_graphic_and_palette(item_id, unit);
    }
}
