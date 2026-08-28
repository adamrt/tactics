#include "psx/types.h"

extern s32* g_debugchr_controller_input;
extern s32 g_menu_text_palette_offset;
extern s32 g_menu_inner_window_width;
extern s32* battle_get_controller_input_pointer(s32 controller);
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
extern void battle_update_menu_selection_from_input(void*, s32*);
extern void battle_handle_menu_action(void*, s32);
extern void battle_handle_menu_cancel_input(void*);
extern void configure_menu_frame_cluts(void*);
extern void battle_update_menu_cursor_primitives(void*, void*, s32, s32);
extern void submit_menu_frame_primitives(void*);
extern void stop_current_event_thread(void);

void debugchr_run_character_editor_menu_thread(void) {
    u8 local_10[8];
    u8 frames[0xf8];
    s32 saved;
    s32 frame;
    s32 redraw;
    s32 render;
    void* state;
    s16* refresh;
    u8* frame_buffer;
    register u8* frame_buffer_base;
    s32* display_x;
    s32 one;
    void* created_state;
    s32* controller_input;
    s32 window_id;
    register s32 call_one __asm__("$7");
    s32 call_frame;
    register void* call_data __asm__("$6");
    void* call_state;
    void* call_current;

    g_debugchr_controller_input = battle_get_controller_input_pointer(0);
    created_state = battle_get_first_thread_parameter();
    frame_buffer = frames;
    __asm__ volatile("" : : "r"(frame_buffer));
    state = created_state;
    *(u16*)((u8*)state + 0xa) &= 0xfffe;
    saved = *(s16*)((u8*)state + 0x38);
    if (saved == -1)
        saved = 0;
    initialize_menu_render_frames(local_10, state, frame_buffer);
    world_copy_bytes(frame_buffer + 0x7c, frame_buffer, 0x7c);
    redraw = 0;
    frame = 0;
    one = 1;
    display_x = &g_menu_inner_window_width;
    frame_buffer_base = frame_buffer;
    refresh = *(s16**)((u8*)state + 0x30);
    *refresh = 1;
    for (;;) {
        u8* current;
        if (*refresh == one) {
            call_data = local_10;
            __asm__("" : "=r"(call_data) : "0"(call_data));
            call_one = 1;
            __asm__("" : "=r"(call_one) : "0"(call_one));
            *refresh = 0;
            redraw = 1;
            render = build_menu_window_image_buffer(*(s16*)((u8*)state + 4),
                *(s16*)((u8*)state + 6), call_data,
                call_one);
            *display_x = *(s16*)((u8*)state + 4);
            world_set_menu_text_origin(8, 9);
            window_id = *(s16*)((u8*)state + 0x1c);
            g_menu_text_palette_offset = 0;
            battle_world_display_menu_text_entry(window_id, render,
                (u8*)display_x - 8);
            LoadImage(local_10, render);
        }
        current = frame_buffer_base + ((frame & 1) * 0x7c);
        advance_event_thread();
        if (redraw == one) {
            battle_free_battle_memory(render);
            redraw = 0;
        }
        controller_input = g_debugchr_controller_input;
        *(s16*)((u8*)state + 0x38) = saved;
        if (battle_should_close_menu_thread(controller_input) != 0)
            break;
        battle_update_menu_selection_from_input(state, &saved);
        battle_handle_menu_action(state, saved);
        battle_handle_menu_cancel_input(state);
        configure_menu_frame_cluts(current);
        call_state = state;
        call_current = current;
        call_frame = frame;
        battle_update_menu_cursor_primitives(call_state, call_current,
            call_frame, saved);
        frame++;
        submit_menu_frame_primitives(current);
    }
    advance_event_thread();
    stop_current_event_thread();
}
