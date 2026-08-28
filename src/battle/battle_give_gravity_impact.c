#include "psx/types.h"

extern void func_8001C268(s32);
extern s32 D_801B8874;
extern s32 g_effect_gravity_modifier;

void battle_give_gravity_impact(void) {
    func_8001C268((g_effect_gravity_modifier * D_801B8874) >> 12);
}
