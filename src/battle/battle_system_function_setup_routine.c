#include "psx/types.h"

extern s32 battle_get_target_id_ptr_by_battle_id(s32);
extern void func_8014175C(s32, s32, s32);
extern void func_80141B0C(s32, s32, s32, s32, s32, s32);

void battle_system_function_setup_routine(s32 type, s32 b, s32 c, s32 d, s32 e) {
    s32 ptr;

    if (type != 8 && type != 6) {
        ptr = battle_get_target_id_ptr_by_battle_id(c);
        if (type == 5) {
            func_8014175C(ptr, c, e);
            return;
        }
        if (type == 7) {
            func_80141B0C(7, 0, c, 0, 0, ptr);
            return;
        }
    }
    func_80141B0C(type, b, c, d, e, ptr);
}
