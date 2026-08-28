#include "psx/types.h"

extern u8* g_target_current_action;
extern void func_80185814(void);

s32 battle_calculate_hit(void) {
    func_80185814();
    return *g_target_current_action == 0;
}
