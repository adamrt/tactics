#include "psx/types.h"

extern s16 world_load_halfword(const void* source);
extern s32 world_try_get_unit_misc_data_by_id(u16* unit_id, s32* misc_index);
extern s32 world_process_unit_misc_state_value(u16* unit_id, s32* unit_index,
    s32* misc_index);
extern void battle_set_idle_animation_by_misc_id(u16 misc_id);
extern void world_wait(s32 frames);

void world_march_units(const u8* parameters) {
    u16 unit_id;
    s32 misc_index;
    s32 unit_index;

    unit_id = world_load_halfword(parameters);
    if (world_try_get_unit_misc_data_by_id(&unit_id, &misc_index) != 0) {
        unit_index = 0;
        do {
            if (world_process_unit_misc_state_value(&unit_id, &unit_index,
                    &misc_index)
                != 0) {
                battle_set_idle_animation_by_misc_id(unit_id);
                world_wait(parameters[2]);
                if (misc_index == 0) {
                    break;
                }
            }
            unit_index++;
        } while (unit_index < 21);
    }
}
