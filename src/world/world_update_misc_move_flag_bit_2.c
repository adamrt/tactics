#include "psx/types.h"

extern s16 world_load_halfword(const void* source);
extern s32 world_try_get_unit_misc_data_by_id(u16* unit_id, s32* misc_index);
extern s32 world_process_unit_misc_state_value(u16* unit_id, s32* unit_index,
    s32* misc_index);
extern void battle_flip_misc_data_move_flag_bit_2(u16 misc_id);
extern void battle_unset_misc_data_move_flag_bit_2(u16 misc_id);

void world_update_misc_move_flag_bit_2(const u8* parameters) {
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
                if (parameters[2] != 0) {
                    battle_flip_misc_data_move_flag_bit_2(unit_id);
                } else {
                    battle_unset_misc_data_move_flag_bit_2(unit_id);
                }
                if (misc_index == 0) {
                    break;
                }
            }
            unit_index++;
        } while (unit_index < 21);
    }
}
