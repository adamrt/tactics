#include "psx/types.h"

extern void* g_menu_descriptor;
extern s32 g_current_event_thread_id;
extern u8 g_option_at_list_state[];
extern const u8 g_option_at_list_entry_table[];
extern const void* g_option_at_list_entry_table_pointer;
extern s16 g_option_at_list_menu_type;

extern void option_configure_at_list(void* state);
extern void option_build_at_list(void);
extern void initialize_event_thread(s32 thread_id, void (*entrypoint)(void));
extern void battle_store_thread_function_parameters(s32 thread_id, void* parameter_0,
    s32 parameter_1, s32 parameter_2);
extern void switch_to_next_event_thread(void);
extern s32 battle_check_thread_running_status(s32 thread_id);
extern void stop_current_event_thread(void);

/* Install the AT-list menu context until both builder threads finish. */
void option_start_at_list_menu_thread(void) {
    void* previous_menu_descriptor = g_menu_descriptor;

    g_option_at_list_menu_type = 0x13;
    g_menu_descriptor = g_option_at_list_state;
    g_option_at_list_entry_table_pointer = g_option_at_list_entry_table;
    option_configure_at_list(g_option_at_list_state);

    initialize_event_thread(g_current_event_thread_id - 2,
        option_build_at_list);
    battle_store_thread_function_parameters(g_current_event_thread_id - 2,
        g_option_at_list_state, 0, 0);

    do {
        switch_to_next_event_thread();
    } while (battle_check_thread_running_status(g_current_event_thread_id - 2) != 0 || battle_check_thread_running_status(g_current_event_thread_id - 3) != 0);

    g_menu_descriptor = previous_menu_descriptor;
    stop_current_event_thread();
}
