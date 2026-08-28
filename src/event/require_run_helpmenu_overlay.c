#include "psx/types.h"

extern void set_current_thread_task_id(s32 task_id);
extern void* game_realloc(void* allocation, u32 size);
extern void switch_to_next_event_thread(void);
extern void setup_companion_executable(s32 id);
extern s32 battle_get_next_available_thread_id(s32 limit);
extern void initialize_event_thread(s32 thread_id, void (*entry)(void));
extern void wait_for_event_thread(s32 thread_id);
extern void stop_current_event_thread(void);
extern void* g_high_overlay_load_address;
extern s32 g_sound_effect_id_to_play;
extern u8 g_require_status_animation[];
extern void helpmenu_run_require_help_menu(void);

void require_run_helpmenu_overlay(void) {
    s32 thread_id;

    set_current_thread_task_id(0x40);
    g_sound_effect_id_to_play = 1;
    g_require_status_animation[0] = 1;
    g_require_status_animation[1] = 1;
    while (game_realloc(g_high_overlay_load_address, 0x10000) != g_high_overlay_load_address) {
        switch_to_next_event_thread();
    }
    setup_companion_executable(3);
    thread_id = battle_get_next_available_thread_id(0x10);
    initialize_event_thread(thread_id, helpmenu_run_require_help_menu);
    wait_for_event_thread(thread_id);
    g_require_status_animation[0] = 0;
    g_require_status_animation[1] = 0;
    stop_current_event_thread();
}
