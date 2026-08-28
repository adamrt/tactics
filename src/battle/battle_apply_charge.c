#include "psx/types.h"

extern u16 g_current_ability_xa;
extern u8 g_current_ability_charge_power;

void battle_apply_charge(void) {
    u16* xa = &g_current_ability_xa;

    *xa += g_current_ability_charge_power;
}
