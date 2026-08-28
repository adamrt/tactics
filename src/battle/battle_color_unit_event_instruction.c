#include "psx/types.h"

extern s16 battle_load_halfword(u8* ptr);
extern s32 try_get_unit_misc_data_by_unit_id(u16* unit_id, s32* out);
extern s32 func_801479AC(u16* unit_id, s32* index, s32* out);
extern void battle_start_misc_unit_palette_modulation(s32 a, s32 b, s32 unit_id, s32 d, s32 e, s32 f);

void battle_color_unit_event_instruction(u8* ptr) {
    u16 unit_id;
    s32 out;
    s32 i;

    unit_id = battle_load_halfword(ptr);
    if (try_get_unit_misc_data_by_unit_id(&unit_id, &out) != 0) {
        ptr += 2;
        i = 0;
        do {
            if (func_801479AC(&unit_id, &i, &out) != 0) {
                battle_start_misc_unit_palette_modulation(ptr[0], ptr[4], unit_id, ((s8*)ptr)[1], ((s8*)ptr)[2], ((s8*)ptr)[3]);
                if (out == 0) {
                    return;
                }
            }
            i += 1;
        } while (i < 0x15);
    }
}
