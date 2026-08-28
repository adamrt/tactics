#include "psx/types.h"

extern s32 g_event_mode;
extern void battle_initialize_menu_primitive_colors_palette_bank_1(void* output);
extern void battle_initialize_menu_primitive_colors_palette_bank_0(void* output);

void require_initialize_menu_primitive_colors(void* output, u8* context) {
    if ((*(s32*)(context + 0x10) == 1) || (g_event_mode == 1)) {
        battle_initialize_menu_primitive_colors_palette_bank_1(output);
    } else {
        battle_initialize_menu_primitive_colors_palette_bank_0(output);
    }
}
