#include "psx/types.h"

extern u32 g_shifted_controller_flags;
extern s32 g_option_reference_values[];
extern s32 g_option_current_values[];
extern s32 g_option_values_unchanged;
extern s16 g_option_menu_open;
extern s32 g_option_menu_state;
extern s32 g_current_event_thread_id;
extern u8 g_option_menu_entry_table[];

extern void* battle_get_first_thread_parameter(void);
extern void battle_store_thread_function_parameters(s32 thread_id, void* parameter_0,
    s32 parameter_1, s32 parameter_2);
extern void wait_for_event_thread(s32 thread_id);
extern void signal_menu_event_to_script(s32 event_code);
extern void initialize_event_thread(s32 thread_id, void (*entrypoint)(void));
extern void option_build_options_menu(void);
extern void option_start_at_list_menu_thread(void);
extern void option_start_dead_unit_menu_threads(void);
extern void stop_current_event_thread(void);

/* Decode saved option fields and dispatch the requested option-menu mode. */
void option_entrypoint(s32 menu_type) {
    u8* menu = battle_get_first_thread_parameter();
    s32 index;
    u32 packed = g_shifted_controller_flags;

    g_option_values_unchanged = 1;
    g_option_current_values[0] = packed & 7;
    g_option_current_values[1] = (packed >> 3) & 7;
    g_option_current_values[2] = (packed >> 6) & 7;
    g_option_current_values[3] = (packed >> 9) & 7;
    g_option_current_values[4] = (packed >> 12) & 7;
    g_option_current_values[5] = (packed >> 15) & 3;
    g_option_current_values[6] = (packed >> 17) & 3;
    g_option_current_values[7] = (packed >> 19) & 3;
    g_option_current_values[8] = (packed >> 25) & 3;
    g_option_current_values[9] = (packed >> 27) & 3;
    g_option_current_values[10] = (packed >> 23) & 3;
    g_option_current_values[11] = (packed >> 29) & 3;
    g_option_current_values[12] = (packed >> 21) & 3;

    for (index = 0; index < 13; index++) {
        if (g_option_current_values[index] != g_option_reference_values[index]) {
            g_option_current_values[13] = 0;
        }
    }

    if (menu_type != 2) {
        battle_store_thread_function_parameters(10, 0, 0, 1);
        battle_store_thread_function_parameters(11, 0, 0, 1);
        battle_store_thread_function_parameters(12, 0, 0, 1);
        battle_store_thread_function_parameters(13, 0, 0, 1);
        wait_for_event_thread(10);
        wait_for_event_thread(11);
        wait_for_event_thread(12);
        wait_for_event_thread(13);
    }

    g_option_menu_open = 0;
    g_option_menu_state = 0;
    if (menu_type == 0) {
        s32 child_thread;

        signal_menu_event_to_script(0xfd);
        initialize_event_thread(g_current_event_thread_id - 1,
            option_build_options_menu);
        child_thread = g_current_event_thread_id;
        *(s16*)(menu + 0x3a) = 1;
        *(void**)(menu + 0x30) = g_option_menu_entry_table;
        battle_store_thread_function_parameters(child_thread - 1, menu, 0, 0);
        wait_for_event_thread(g_current_event_thread_id - 1);
        stop_current_event_thread();
    }
    if (menu_type == 1) {
        signal_menu_event_to_script(0xf9);
        option_start_at_list_menu_thread();
    }
    if (menu_type == 2) {
        option_start_dead_unit_menu_threads();
    }
}
