#include "psx/types.h"

extern s32 g_battle_at_list_active;
extern void func_800890b8(s16* primary, s16* secondary, s16* tertiary);
extern void func_8008924c(void);

void battle_calculate_tile_coords_and_glow_from_at_list(void) {
    s16 secondary[4];
    s16 tertiary[4];
    s16 primary[8];

    if (g_battle_at_list_active != 0) {
        func_8008924c();
        return;
    }
    func_800890b8(primary, secondary, tertiary);
}
