#include "psx/types.h"

extern s32 g_bunit_selection_text_id;
extern s32 D_801ECB68;
extern s32 g_event_mode;
extern u8 D_801CFDF8;
extern void text_character_handling_thread(void);
extern void battle_save_text_pointer_table(void);
extern void battle_relocate_text_pointer_table(void* ptr);
extern void battle_thread_initialize(s32 id, void (*func)(void));
extern void battle_store_thread_function_parameters(s32 id, void* a1, s32 a2, s32 a3);

/* Start the text thread for g_bunit_selection_text_id (ids above 0x1FFFF are
 * stashed in D_801ECB68 instead); menu_state + 0x38 is the saved selection. */
void bunit_start_selection_text_thread(u8* menu_state) {
    if (g_bunit_selection_text_id > 0x1FFFF) {
        D_801ECB68 = g_bunit_selection_text_id;
        return;
    }
    if (g_bunit_selection_text_id <= 0) {
        return;
    }
    battle_save_text_pointer_table();
    battle_relocate_text_pointer_table(&D_801CFDF8);
    battle_thread_initialize(1, text_character_handling_thread);
    battle_store_thread_function_parameters(1, menu_state + 0x38, g_bunit_selection_text_id, 0);
    g_event_mode = 1;
}
