#include "psx/types.h"

extern u16 g_current_ability_id;
extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern u8* g_target_current_action;
extern void apply_compatibility(void);

void battle_store_xa_plus_ya_status_damage(void) {
    u16 original_xa;

    if (g_current_ability_id != 0x41) {
        original_xa = g_current_ability_xa;
        g_current_ability_xa = g_current_ability_ya;
        apply_compatibility();
        g_current_ability_ya = g_current_ability_xa;
        g_current_ability_xa = original_xa;
    }
    *(u16*)(g_target_current_action + 4) = g_current_ability_xa + g_current_ability_ya;
}
