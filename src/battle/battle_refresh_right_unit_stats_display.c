#include "psx/types.h"

extern u8 g_battle_right_unit_stats_display[];
extern s16 g_battle_right_unit_display_mode;
extern s16 g_battle_right_unit_banner_field_4;
extern void battle_store_units_small_in_battle_display_data(void);
extern void battle_display_hovered_unit_stats(void* display, s32 mode,
    void* scratch,
    void* unit_banner);

void battle_refresh_right_unit_stats_display(void) {
    s16* display_mode;
    s16* banner_field;

    battle_store_units_small_in_battle_display_data();
    display_mode = &g_battle_right_unit_display_mode;
    banner_field = &g_battle_right_unit_banner_field_4;
    *display_mode = 2;
    if (*banner_field < 0) {
        *display_mode = 0x0c00;
    }
    battle_display_hovered_unit_stats(
        g_battle_right_unit_stats_display, 3,
        (u8*)display_mode - 0x50, (u8*)banner_field - 4);
}
