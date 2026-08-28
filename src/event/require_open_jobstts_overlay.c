#include "psx/types.h"

extern void battle_copy_active_turn_data_from(void*, void*, void*);
extern void* game_realloc(void*, u32);
extern void* g_high_overlay_load_address;
extern s32 g_font_print_enabled;
extern void FntPrint(const char* text);
extern const char g_jobstts_wait_for_allocation_message[];
extern void switch_to_next_event_thread(void);
extern void setup_companion_executable(s32 id);
extern void wait_frames(s32 frames);
extern s32 g_companion_overlay_state;
extern s32* battle_get_controller_input_pointer(s32 controller);
extern s32* g_require_controller_input;
extern void main_game_free(void* allocation);
extern s16 g_option_menu_open;
extern void stop_current_event_thread(void);
extern u8 g_require_active_unit_banner[];
extern u8 g_require_active_unit_data[];
extern u8 g_require_billboard_data[];

void require_open_jobstts_overlay(void) {
    void* allocation;

    battle_copy_active_turn_data_from(g_require_active_unit_banner,
        g_require_active_unit_data,
        g_require_billboard_data);
    while (1) {
        allocation = game_realloc(g_high_overlay_load_address, 0x1f000);
        if (allocation == g_high_overlay_load_address) {
            break;
        }
        switch_to_next_event_thread();
        if (g_font_print_enabled != 0) {
            FntPrint(g_jobstts_wait_for_allocation_message);
        }
    }
    setup_companion_executable(7);
    wait_frames(2);
    g_companion_overlay_state = 3;
    do {
        g_require_controller_input = battle_get_controller_input_pointer(0);
        *g_require_controller_input = 0;
        switch_to_next_event_thread();
    } while (g_companion_overlay_state != 0);
    *g_require_controller_input = 0;
    main_game_free(allocation);
    wait_frames(2);
    g_option_menu_open = 0;
    stop_current_event_thread();
}
