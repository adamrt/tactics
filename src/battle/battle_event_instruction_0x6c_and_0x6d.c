#include "psx/types.h"

extern s32 try_get_unit_misc_data_by_unit_id(u16* unit_id, s32* out);
extern s32 func_801479AC(u16* unit_id, s32* index, s32* out);
extern void battle_unset_misc_data_move_flag_bit_3(u16 unit_id);
extern void battle_flip_misc_data_move_flag_bit_3(u16 unit_id);

void battle_event_instruction_0x6c_and_0x6d(s16 arg0, s32 flip) {
    u16 unit_id;
    s32 out;
    s32 i;

    unit_id = arg0;
    if (try_get_unit_misc_data_by_unit_id(&unit_id, &out) != 0) {
        i = 0;
        do {
            if (func_801479AC(&unit_id, &i, &out) != 0) {
                if (flip == 0) {
                    battle_unset_misc_data_move_flag_bit_3(unit_id);
                } else {
                    battle_flip_misc_data_move_flag_bit_3(unit_id);
                }
                if (out == 0) {
                    return;
                }
            }
            i += 1;
        } while (i < 0x15);
    }
}
