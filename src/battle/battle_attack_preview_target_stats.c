#include "psx/types.h"

extern s32 D_8016C8B8;
extern s16 g_selected_unit_index;
extern u16 g_battle_preview_target_unit_id;
extern u16 D_8014D0AE;
extern u16 D_8014D0D2;
extern u16 D_8014D0EE;
extern u16 D_8014D112;
extern u8 D_8014D05C[];
extern u8 D_80168658[];
extern u8 D_801687B8[];

extern void wait_for_event_thread(s32 thread_id);
extern void switch_to_next_thread(void);
extern void battle_store_units_small_in_battle_display_data(void);
extern void battle_display_hovered_unit_stats(u8* a, s32 b, u8* c, u8* d);

void battle_attack_preview_target_stats(void) {
    s16* sel;
    s32 saved;

    if (D_8016C8B8 != 0x13) {
        wait_for_event_thread(0xC);
    }
    switch_to_next_thread();
    switch_to_next_thread();
    sel = &g_selected_unit_index;
    saved = *sel;
    *sel = g_battle_preview_target_unit_id;
    battle_store_units_small_in_battle_display_data();
    *sel = saved;
    D_8014D0EE = D_8014D0AE;
    D_8014D112 = D_8014D0D2;
    battle_store_units_small_in_battle_display_data();
    battle_display_hovered_unit_stats(D_80168658, 2, D_801687B8, D_8014D05C);
}
