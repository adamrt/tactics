#include "psx/types.h"

extern s32 g_event_mode;
extern void battle_initialize_menu_primitive_colors_palette_bank_0(void);
extern void battle_initialize_menu_primitive_colors_palette_bank_1(void);

void attack_apply_menu_palette_for_mode(s32 unused, s32* arg1) {
    if (arg1[4] == 1 || g_event_mode == 1) {
        battle_initialize_menu_primitive_colors_palette_bank_1();
    } else {
        battle_initialize_menu_primitive_colors_palette_bank_0();
    }
}
