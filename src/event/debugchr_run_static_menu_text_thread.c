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

void debugchr_run_static_menu_text_thread(void) {
    u8 local_10[8];
    u8 frames[0xf8];
    u8* frame_pair;
    u8* frame_base;
    s32* display_x;
    s32 done = 0;
    s32 frame;
    s32 redraw;
    s32 render;
    s32 frame_parity;
    s32 frame_offset;
    void* state = battle_get_first_thread_parameter();

    frame_pair = frames;
    initialize_menu_render_frames(local_10, state, frame_pair);
    world_copy_bytes(frame_pair + 0x7c, frame_pair, 0x7c);
    redraw = 1;
    frame = 0;
    display_x = &g_menu_inner_window_width;
    frame_base = frame_pair;
    for (;;) {
        if (frame == (frame / 7) * 7) {
            redraw = 1;
            render = build_menu_window_image_buffer(*(s16*)((u8*)state + 4),
                *(s16*)((u8*)state + 6), local_10, 1);
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
        if (battle_should_close_menu_thread(&done) != 0)
            break;
        frame_parity = frame & 1;
        frame_offset = frame_parity << 5;
        frame_offset -= frame_parity;
        frame_offset <<= 2;
        frame_pair = frame_base + frame_offset;
        configure_menu_frame_cluts(frame_pair);
        submit_menu_frame_primitives(frame_pair);
        frame++;
    }
    advance_event_thread();
    stop_current_event_thread();
}
