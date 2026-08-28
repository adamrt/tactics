#include "psx/types.h"

extern s16 world_load_halfword(const void* source);
extern s32 world_try_get_unit_misc_data_by_id(u16* unit_id, s32* misc_index);
extern s32 world_process_unit_misc_state_value(u16* unit_id, s32* unit_index,
    s32* misc_index);
extern void battle_start_misc_unit_palette_modulation(u8 preset_color, u8 time, u16 misc_id, s8 red,
    s8 green, s8 blue);

void world_color_units(const u8* parameters) {
    u16 unit_id;
    s32 misc_index;
    s32 unit_index;

    unit_id = world_load_halfword(parameters);
    if (world_try_get_unit_misc_data_by_id(&unit_id, &misc_index) != 0) {
        parameters += 2;
        unit_index = 0;
        do {
            if (world_process_unit_misc_state_value(&unit_id, &unit_index,
                    &misc_index)
                != 0) {
                battle_start_misc_unit_palette_modulation(parameters[0], parameters[4], unit_id,
                    (s8)parameters[1], (s8)parameters[2],
                    (s8)parameters[3]);
                if (misc_index == 0) {
                    break;
                }
            }
            unit_index++;
        } while (unit_index < 21);
    }
}
