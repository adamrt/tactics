#include "psx/types.h"

extern s32 g_equip_help_message_id;
extern void* D_801CFBD8;
extern void battle_save_text_pointer_table(void);
extern void battle_relocate_text_pointer_table(void*);
extern void initialize_event_thread(s32, void*);
extern void battle_store_thread_function_parameters(s32, s32, s32, s32);
extern void text_character_handling_thread(void);
extern s32 g_event_mode;

void equip_start_help_text_thread(s32 arg0) {
    if (g_equip_help_message_id > 0) {
        battle_save_text_pointer_table();
        battle_relocate_text_pointer_table(&D_801CFBD8);
        initialize_event_thread(1, text_character_handling_thread);
        battle_store_thread_function_parameters(1, arg0 + 0x38, g_equip_help_message_id, 0);
        g_event_mode = 1;
    }
}
