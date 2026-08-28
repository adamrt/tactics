#include "psx/gpu.h"
#include "psx/types.h"

typedef struct CardMenuRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} CardMenuRect;

extern s16 g_card_otag_length;
extern s16 g_card_poly_ft4_capacity;
extern s16 g_card_tile_capacity;
extern u16 g_card_input_newly_pressed;
extern u16 g_card_drawenv_y;
extern u16 g_card_input_primary_repeat;
extern u8 g_card_save_menu_state;
extern s16 g_card_state_801c9576;
extern s16 g_card_state_801c957c;
extern CardMenuRect g_card_fullscreen_fade_rect;
extern u8 g_card_fade_overlay_color[3];
extern POLY_FT4 g_card_poly_ft4_buffers[];
extern u8* g_card_save_menu_work_buffer;
extern u32** g_card_graphics_context;
extern u32* g_current_otag_entry;
extern s32 g_sound_effect_id_to_play;
extern s32 g_suppress_sound_effect_playback;
extern u8 g_card_queued_sound_effect_id;

extern void card_initialize_graphics_contexts(
    void* contexts, void* otags, s32 arg2, s32 arg3, s32 arg4, void* polygons,
    s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11,
    s32 arg12, s32 arg13, s32 arg14, s32 arg15, void* tiles, s32 arg17,
    s32 arg18, s32 arg19, s32 arg20, s32 arg21, s32 arg22, s32 arg23,
    s32 arg24);
extern void card_initialize_save_menu_graphics(void);
extern s32 open_music_into_free_slot(s32 id);
extern s32 main_unused_music_stub(void);
extern void switch_music_track(s32 slot, s32 volume, s32 unused);
extern void card_consume_all_events(void);
extern void card_initialize_save_menu_state(void);
extern void initialize_event_thread(s32 id, void (*entry)(void));
extern void battle_store_thread_function_parameters(s32 id, s32 first, s32 second,
    s32 third);
extern s32 card_update_increasing_fade(void);
extern void card_submit_frame_and_swap_buffers(s32 first_otag, s32 draw_otag);
extern void card_update_input_and_suppress_during_fade(void);
extern void card_update_decreasing_fade(void);
extern void card_enqueue_translucent_tile(const CardMenuRect* rect,
    const u8* color, s32 semitrans,
    s32 otag_index);
extern s32 is_event_thread_running(s32 id);
extern void func_801c1fc8(u16 input);
extern void card_update_initial_save_prompt(void);
extern void card_update_memory_card_slot_selection(void);
extern void func_801c0c58(void);
extern void card_update_save_slot_scan_result(void);
extern void card_update_save_slot_write_operation(s32 state);
extern void main_set_current_music_target(s32 slot, s32 target);
extern s32 card_poll_operation_result(void);
extern void card_start_fade_from_zero(void);
extern void card_set_render_otag(u32* otag);
extern void func_8012e65c(void);
extern s32 main_read_controller_input(s32 unused);
extern void func_801c3a4c(void* state, s32 input, s32 drawenv_y);
extern void main_play_sound(s32 sound_id);
extern void unload_scenario_music(s32 slot);
extern void card_run_save_menu_graphic_thread(void);

void card_run_save_menu(s32 unused) {
    u8 tile_storage[0x140];
    u8 otag_storage[0x200];
    u8 context_storage[0x1f8];
    volatile s32 leading_alignment;
    s32 input;
    s32 unused_local;
    s32 buttons;
    u16 menu_input;
    volatile u16 alignment;
    s16 music_slot;
    u8 save_buffer[0x258];

    g_card_otag_length = 0x40;
    g_card_poly_ft4_capacity = 0x258;
    g_card_tile_capacity = 10;
    card_initialize_graphics_contexts(
        context_storage, otag_storage, 0, 0, 0, g_card_poly_ft4_buffers, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, tile_storage, 0, 0, 0, 0, 0, 0, 0, 0);
    card_initialize_save_menu_graphics();
    music_slot = open_music_into_free_slot(0x29);
    while (main_unused_music_stub() != 0) {
    }
    switch_music_track(music_slot, 0x7f, 0);
    card_consume_all_events();
    g_card_save_menu_work_buffer = save_buffer;
    card_initialize_save_menu_state();
    initialize_event_thread(2, card_run_save_menu_graphic_thread);
    battle_store_thread_function_parameters(2, 0, 0, 0);
    g_card_state_801c957c = 0;

    while (card_update_increasing_fade() != 0) {
        card_submit_frame_and_swap_buffers(0, 0);
        card_update_input_and_suppress_during_fade();
        card_update_decreasing_fade();
        card_enqueue_translucent_tile(&g_card_fullscreen_fade_rect,
            g_card_fade_overlay_color, 0, 0);

        menu_input = g_card_save_menu_state == 4 && is_event_thread_running(5) == 0
            ? g_card_input_primary_repeat
            : 0;
        if (g_card_save_menu_state >= 4 && g_card_save_menu_state < 7) {
            func_801c1fc8(menu_input);
        }

        if (g_card_save_menu_state == 0) {
            card_update_initial_save_prompt();
        } else if (g_card_save_menu_state == 1) {
            card_update_memory_card_slot_selection();
        } else if (g_card_save_menu_state == 3) {
            func_801c0c58();
        } else if (g_card_save_menu_state == 2) {
            card_update_save_slot_scan_result();
        } else if (g_card_save_menu_state == 6) {
            card_update_save_slot_write_operation(g_card_state_801c9576);
        } else if (g_card_save_menu_state == 10 || g_card_save_menu_state == 9) {
            main_set_current_music_target(0, 0xf0);
            while (card_poll_operation_result() == -1) {
            }
            card_start_fade_from_zero();
            g_card_save_menu_state = 0xff;
        }

        card_set_render_otag(*g_card_graphics_context + 1);
        g_current_otag_entry = *g_card_graphics_context + 0x3c;
        func_8012e65c();
        input = main_read_controller_input(0) & 0xf000;
        buttons = g_card_input_newly_pressed & 0x0fff;
        input |= buttons;
        if (is_event_thread_running(1) == 0 && is_event_thread_running(5) == 0 && is_event_thread_running(14) == 0) {
            input &= 0xff00;
        }
        func_801c3a4c(*g_card_graphics_context + 0x3c, input,
            g_card_drawenv_y == 0 ? 0xf0 : 0);

        if (g_sound_effect_id_to_play == 3 || g_sound_effect_id_to_play == 2) {
            g_card_queued_sound_effect_id = g_sound_effect_id_to_play;
        }
        if (g_sound_effect_id_to_play < 0 || g_suppress_sound_effect_playback != 0) {
            g_sound_effect_id_to_play = 0;
        }
        input = g_sound_effect_id_to_play != 0 ? g_sound_effect_id_to_play
                                               : g_card_queued_sound_effect_id;
        if (input != 0) {
            main_play_sound(input);
        }
        g_card_queued_sound_effect_id = 0;
        g_sound_effect_id_to_play = 0;
    }

    battle_store_thread_function_parameters(2, 0, -1, 0);
    unload_scenario_music(music_slot);
}
