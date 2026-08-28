#include "psx/types.h"

extern s32 g_require_suspended_thread_id;
extern u8 g_require_status_group_count;
extern u8* g_event_threads;
extern u8 g_require_poly_gt4_banks[];
extern u8 g_require_poly_ft4_banks[];
extern void mark_thread_stopped(s32 id);
extern void* allocate_battle_memory(s32 bytes);
extern void battle_free_battle_memory(void* memory);
extern void world_copy_bytes(void* destination, const void* source, s32 count);
extern void require_render_transition_poly_gt4_grid(void* frame);
extern void require_render_transition_poly_ft4_passes(void* frame);
extern void switch_to_next_event_thread(void);
extern s32 battle_get_third_thread_parameter(void);
extern void mark_thread_running(s32 id);
extern void stop_current_event_thread(void);

void require_run_suspended_thread_transition(void) {
    s32 frame = 0;
    u8* saved;

    mark_thread_stopped(g_require_suspended_thread_id);
    saved = allocate_battle_memory(0x400);
    world_copy_bytes(
        saved,
        g_event_threads + g_require_suspended_thread_id * 0x400,
        0x400);
    g_require_status_group_count = 2;
    while (1) {
        s32 buffer = frame & 1;
        require_render_transition_poly_gt4_grid(
            g_require_poly_gt4_banks + buffer * 0x820);
        require_render_transition_poly_ft4_passes(
            g_require_poly_ft4_banks + buffer * 0x4b0);
        switch_to_next_event_thread();
        if (battle_get_third_thread_parameter() != 0) {
            break;
        }
        frame++;
    }
    world_copy_bytes(
        g_event_threads + g_require_suspended_thread_id * 0x400,
        saved, 0x400);
    battle_free_battle_memory(saved);
    mark_thread_running(g_require_suspended_thread_id);
    switch_to_next_event_thread();
    stop_current_event_thread();
}
