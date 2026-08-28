#include "psx/types.h"

extern s32 g_unit_graphics_load_count;
extern s32 D_80096108;
extern s32 D_800459a0[];
extern s32 g_battle_graphics_state_words[4];

extern s32 battle_get_script_variable(s32 id);
extern s32* func_801c5a50(void);
extern void func_8017f5f8(s32* p, s32 flag);
extern void battle_prep_for_initialize_deployed_units_data(s32* p, s32 flag);

void battle_80088868(void) {
    g_unit_graphics_load_count = 0;
    if (battle_get_script_variable(0x1FE) == 0) {
        if (D_80096108 != 0) {
            battle_prep_for_initialize_deployed_units_data(D_800459a0, 0);
            g_battle_graphics_state_words[0] = 0;
            g_battle_graphics_state_words[1] = 0;
            g_battle_graphics_state_words[2] = 0;
            g_battle_graphics_state_words[3] = 0;
            return;
        }
    } else {
        func_8017f5f8(func_801c5a50(), 0);
    }
    battle_prep_for_initialize_deployed_units_data(func_801c5a50(), 0);
    g_battle_graphics_state_words[0] = 0;
    g_battle_graphics_state_words[1] = 0;
    g_battle_graphics_state_words[2] = 0;
    g_battle_graphics_state_words[3] = 0;
}
