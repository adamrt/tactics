#include "psx/types.h"

extern u8* g_event_threads;
extern s32 g_current_event_thread_id;
extern s32* g_debugchr_controller_input;
extern s32* battle_get_controller_input_pointer(s32 controller);
extern void battle_handle_menu_action(u8* state, s32 value);
extern void initialize_event_thread(s32 thread_id, void (*entry)(void));
extern void text_character_handling_thread(void);
extern void store_thread_parameters_5(s32, u16, u16, u16, u16);
extern void wait_for_event_thread(s32 thread_id);
extern void stop_current_event_thread(void);

void debugchr_open_submenu_thread_from_current(void) {
    u8* state;
    u8* parameters;
    s32* input;
    u16 thread_id;
    u16 parameter_0;
    u16 parameter_1;
    u16 parameter_2;

    state = ((u8**)g_event_threads)[g_current_event_thread_id << 8];
    (*(void (**)(void))(*(u8**)(state + 0x30)))();
    input = battle_get_controller_input_pointer(0);
    parameter_1 = *(u16*)(state + 0x1c);
    parameters = *(u8**)(state + 0x30);
    parameter_0 = *(u16*)(state + 0x2c);
    g_debugchr_controller_input = input;
    thread_id = *(u16*)(parameters + 6);
    parameter_2 = *(u16*)(parameters + 4);
    *input = 0x20;
    battle_handle_menu_action(state, 0);
    initialize_event_thread(thread_id, text_character_handling_thread);
    store_thread_parameters_5(thread_id, parameter_0, parameter_1,
        parameter_2, parameter_2);
    wait_for_event_thread(g_current_event_thread_id - 1);
    wait_for_event_thread(thread_id);
    stop_current_event_thread();
}
