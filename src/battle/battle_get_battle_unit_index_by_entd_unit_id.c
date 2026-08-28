#include "psx/types.h"

extern s32 func_80133158(void);
extern s32 battle_get_battle_unit_index_by_misc_id(s32);

s32 battle_get_battle_unit_index_by_entd_unit_id(void) {
    s32 misc_id = func_80133158();
    if (misc_id != 0x7D0) {
        s32 idx = battle_get_battle_unit_index_by_misc_id(misc_id);
        if (idx != -1) {
            return idx;
        }
    }
    return 0x7D0;
}
