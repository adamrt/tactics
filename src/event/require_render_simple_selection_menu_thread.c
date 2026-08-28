#include "psx/types.h"

extern s32 g_menu_inner_window_width;
extern void* battle_get_first_thread_parameter(void);
extern void initialize_menu_render_frames(void*, void*, void*);
extern void world_copy_bytes(void*, const void*, s32);
extern s32 build_menu_window_image_buffer(s16, s16, void*, s32);
extern void world_set_menu_text_origin(s32, s32);
extern void battle_world_display_menu_text_entry(s16, s32, void*);
extern void LoadImage(void*, s32);
extern void switch_to_next_event_thread(void);
extern void battle_free_battle_memory(s32);
extern s32 battle_should_close_menu_thread(s32*);
extern void configure_menu_frame_cluts(void*);
extern void submit_menu_frame_primitives(void*);
extern void stop_current_event_thread(void);

void require_render_simple_selection_menu_thread(void) {
    struct {
        u8 menu[8];
        u8 frames[0xf8];
    } display;
    s32 done = 0;
    s32 frame;
    s32 allocated;
    s32 render;
    s32* menu_inner_width;
    u8* state;
    u8* frame_base;
    u8* saved_frame_base;
    u8* menu_data;

    state = battle_get_first_thread_parameter();
    frame_base = display.frames;
    __asm__("" : : "r"(frame_base));
    menu_data = display.menu;
    initialize_menu_render_frames(menu_data, state, frame_base);
    world_copy_bytes(frame_base + 0x7c, frame_base, 0x7c);
    allocated = 1;
    frame = 0;
    menu_inner_width = &g_menu_inner_window_width;
    saved_frame_base = frame_base;
    for (;;) {
        u8* current;
        s32 buffer;
        register s32 frame_offset __asm__("$2");
        if (frame == (frame / 7) * 7) {
            allocated = 1;
            render = build_menu_window_image_buffer(*(s16*)(state + 4), *(s16*)(state + 6), display.menu, 1);
            world_set_menu_text_origin(8, 9);
            *menu_inner_width = *(s16*)(state + 4);
            battle_world_display_menu_text_entry(*(s16*)(state + 0x1c), render,
                (u8*)menu_inner_width - 8);
            LoadImage(display.menu, render);
        }
        switch_to_next_event_thread();
        if (allocated == 1) {
            battle_free_battle_memory(render);
            allocated = 0;
        }
        if (battle_should_close_menu_thread(&done) != 0)
            break;
        buffer = frame & 1;
        frame_offset = ((buffer << 5) - buffer) << 2;
        current = saved_frame_base + frame_offset;
        configure_menu_frame_cluts(current);
        submit_menu_frame_primitives(current);
        frame++;
    }
    switch_to_next_event_thread();
    stop_current_event_thread();
}
