#include "psx/types.h"

extern s32 g_menu_inner_window_width;
extern void* battle_get_first_thread_parameter(void);
extern void initialize_menu_render_frames(void*, void*, void*);
extern void world_copy_bytes(void*, const void*, s32);
extern s32 build_menu_window_image_buffer(s16, s16, void*, s32);
extern void world_set_menu_text_origin(s32, s32);
extern void battle_world_display_menu_text_entry(s16, s32, void*);
extern void LoadImage(void*, s32);
extern void advance_event_thread(void);
extern void battle_free_battle_memory(s32);
extern s32 battle_should_close_menu_thread(s32*);
extern void configure_menu_frame_cluts(void*);
extern void submit_menu_frame_primitives(void*);
extern void stop_current_event_thread(void);

void bunit_render_simple_selection_menu_thread(void) {
    u8 local_10[8];
    u8 frames[0xf8];
    s32 close_flag;
    void* state;
    u8* frame_buffer;
    register void* window;
    register u8* frame_buffer_base;
    s32* display_x;
    s32 redraw;
    s32 frame;
    s32 render;
    /* Pin: the per-frame byte offset must be formed in $v0 (target reuses it
     * as the call scratch); unpinned GCC folds it into the addu operand. */
    register s32 offset __asm__("$2");
    s32 bank;

    close_flag = 0;
    frame_buffer = frames;
    window = local_10;
    state = battle_get_first_thread_parameter();
    /* Scheduling fence (emits nothing): forces `addiu s0,sp,0x18` to be issued
     * before the a0/a1 argument setup; the scheduler otherwise sinks it below
     * `move a1,s2` regardless of where the assignment sits in the source. */
    __asm__ volatile("" : : "r"(frame_buffer), "r"(window));
    initialize_menu_render_frames(window, state, frame_buffer);
    world_copy_bytes(frame_buffer + 0x7c, frame_buffer, 0x7c);
    redraw = 1;
    frame = 0;
    display_x = &g_menu_inner_window_width;
    frame_buffer_base = frame_buffer;
    for (;;) {
        u8* current;
        if (frame == (frame / 7) * 7) {
            redraw = 1;
            render = build_menu_window_image_buffer(*(s16*)((u8*)state + 4),
                *(s16*)((u8*)state + 6),
                local_10, 1);
            world_set_menu_text_origin(8, 9);
            *display_x = *(s16*)((u8*)state + 4);
            battle_world_display_menu_text_entry(*(s16*)((u8*)state + 0x1c), render,
                (u8*)display_x - 8);
            LoadImage(local_10, render);
        }
        advance_event_thread();
        if (redraw == 1) {
            battle_free_battle_memory(render);
            redraw = 0;
        }
        if (battle_should_close_menu_thread(&close_flag) != 0) {
            break;
        }
        bank = frame & 1;
        offset = bank * 0x7c;
        current = frame_buffer_base + offset;
        configure_menu_frame_cluts(current);
        submit_menu_frame_primitives(current);
        frame++;
    }
    advance_event_thread();
    stop_current_event_thread();
}
