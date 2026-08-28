#include "psx/types.h"

extern void set_current_thread_task_id(s32 task_id);
extern u8* get_battle_stats_pointer(s32 unit_id);
extern void debugchr_load_selected_unit_into_editor(void);
extern void world_copy_bytes(void* destination, const void* source, s32 size);
extern void initialize_event_thread(s32 id, void (*entry)(void));
extern void battle_store_thread_function_parameters(s32 id, void* first, s32 second,
    s32 third);
extern void advance_event_thread(void);
extern s32* battle_get_controller_input_pointer(s32 controller);
extern void debugchr_render_status_text_primitives(void* primitives);
extern s32 battle_check_thread_running_status(s32 id);
extern s32 battle_get_thread_running_task(s32 task_id);
extern s32 get_previous_event_thread_running_status(void);
extern s32 battle_has_status_effect_for_status_window(s16 unit_id);
extern void battle_copy_active_turn_data_from(void* destination,
    const void* source,
    const void* extra);

extern void debugchr_run_character_debug_display_thread(void);
extern void debugchr_run_character_status_thread(void);
extern void debugchr_run_numeric_editor_thread(void);
extern void debugchr_text_character_handling_thread(void);

extern s32 g_sound_effect_id_to_play;
extern s16 g_option_menu_open;
extern s32 g_event_mode;
extern s32 g_help_menu_open;
extern s32 g_current_event_thread_id;
extern u8* g_menu_descriptor;

extern s32 g_debugchr_editor_active;
extern s16 g_debugchr_unit_id_801c52e6;
extern s16 g_debugchr_unit_id_801c5324;
extern s16 g_debugchr_selected_unit_id;
extern s16 g_debugchr_editor_unit_fields[];
extern volatile u8 g_debugchr_unit_ids[];
extern volatile u8 g_debugchr_unit_ids_for_previous[] __asm__("g_debugchr_unit_ids");
extern volatile u8 g_debugchr_unit_ids_for_next[] __asm__("g_debugchr_unit_ids");
extern u8 g_debugchr_status_group_count;
extern u8 g_debugchr_status_animation[];
extern s32 g_debugchr_thread_refresh_a;
extern s32 g_debugchr_thread_refresh_b;
extern s32 g_debugchr_thread_refresh_c;
extern s32 g_debugchr_panel_refresh_a;
extern s32 g_debugchr_panel_refresh_b;
extern s32 g_debugchr_panel_refresh_c;
extern s32* g_debugchr_controller_input;
extern s32 g_debugchr_comparison_index;
extern s16 g_debugchr_display_mode;
extern u8 g_debugchr_editor_template[];
extern u8 g_debugchr_editor_template_normal[];
extern u8 g_debugchr_editor_template_special[];
extern u8 g_debugchr_render_buffers[];

void debugchr_run_unit_debug_editor_thread(s32 unit_id) {
    s32 frame;
    s32 one;
    register u8* animation __asm__("$19");
    u8* render_buffers;
    s16* selected_unit;
    u8* animation_second;
    u8* animation_third;
    s32 sound_latched;
    s32 event_mode;
    u8* unit;
    s32 input;
    register s32 comparison __asm__("$3");
    const u8* template_source;
    u8* template_destination;

    set_current_thread_task_id(0x3e);
    g_debugchr_editor_active = 0;
    g_debugchr_status_group_count = 2;
    unit = get_battle_stats_pointer(unit_id);
    g_debugchr_unit_ids[0] = unit_id;
    {
        s32 unit_flags;
        s32 initial_selected;
        s32 initial_comparison;
        s32 initial_type;

        unit_flags = *(volatile u8*)(unit + 0x182);
        initial_selected = g_debugchr_unit_ids[0];
        initial_comparison = g_debugchr_unit_ids[0];
        initial_type = g_debugchr_unit_ids[0];
        g_debugchr_unit_ids[1] = unit_flags & 0x1f;
        g_debugchr_selected_unit_id = initial_selected;
        g_debugchr_unit_id_801c5324 = initial_comparison;
        g_debugchr_unit_id_801c52e6 = initial_type;
    }
    debugchr_load_selected_unit_into_editor();
    g_debugchr_comparison_index = 0;

    if (g_debugchr_display_mode != 0) {
        template_destination = g_debugchr_editor_template;
        template_source = g_debugchr_editor_template_special;
        goto copy_editor_template;
    }
    goto use_normal_template;

shutdown_threads:
    battle_store_thread_function_parameters(8, 0, 0, 1);
    battle_store_thread_function_parameters(0xc, 0, 0, 1);
    battle_store_thread_function_parameters(9, 0, 0, 1);
    g_sound_effect_id_to_play = 2;
    goto restore_selected_unit;

use_normal_template:
    template_destination = g_debugchr_editor_template;
    template_source = g_debugchr_editor_template_normal;

copy_editor_template:
    world_copy_bytes(template_destination, template_source, 0xa8);
    g_debugchr_editor_template[0x306] = 0xe;
    /* Keeps the template store ahead of the thread-setup constant loads. */
    __asm__ volatile("" : : : "memory");

    {
        s32* refresh_a;
        s32* refresh_b;
        s32* refresh_c;

        refresh_a = &g_debugchr_thread_refresh_a;
        refresh_b = &g_debugchr_thread_refresh_b;
        refresh_c = &g_debugchr_thread_refresh_c;
        *refresh_a = 0;
        *refresh_b = 0;
        *refresh_c = 0;
        initialize_event_thread(8, debugchr_run_character_debug_display_thread);
        battle_store_thread_function_parameters(8, (u8*)refresh_a - 0x10, 0, 0);
        initialize_event_thread(0xc, debugchr_run_numeric_editor_thread);
        battle_store_thread_function_parameters(0xc, (u8*)refresh_b - 0x10, 0, 0);
        initialize_event_thread(9, debugchr_run_character_status_thread);
        battle_store_thread_function_parameters(9, (u8*)refresh_c - 0x10, 0, 0);
    }

    frame = 0;
    render_buffers = g_debugchr_render_buffers;
    one = 1;
    animation = g_debugchr_status_animation;
    animation_second = animation + 1;
    animation_third = animation + 2;
    selected_unit = &g_debugchr_selected_unit_id;
    g_option_menu_open = 0;

    for (;;) {
        advance_event_thread();
        g_debugchr_controller_input = battle_get_controller_input_pointer(0);
        {
            s32 render_offset;
            render_offset = (frame & 1) * 0x4b0;
            debugchr_render_status_text_primitives(
                (void*)(render_offset + (s32)render_buffers));
        }

        if (battle_check_thread_running_status(3) != 0) {
            if (sound_latched == 0) {
                g_sound_effect_id_to_play = one;
                sound_latched = 1;
            }
            if (battle_get_thread_running_task(1) != 0) {
                g_debugchr_thread_refresh_a = one;
                g_debugchr_thread_refresh_b = one;
                g_debugchr_thread_refresh_c = one;
            } else {
                g_debugchr_thread_refresh_a = 0;
                g_debugchr_thread_refresh_b = 0;
                g_debugchr_thread_refresh_c = 0;
            }
            animation[0] = one;
            animation[1] = one;
            animation[2] = one;
            goto next_frame;
        }

        event_mode = g_event_mode;
        sound_latched = 0;
        animation[0] = 0;
        animation[1] = 0;
        animation[2] = 0;

        if (event_mode == 0 && g_help_menu_open == 0 && get_previous_event_thread_running_status() == 0) {
            input = *g_debugchr_controller_input;
            if ((input & 0x40) != 0)
                goto shutdown_threads;
            if ((input & 0x20) != 0 && battle_check_thread_running_status(3) == 0 && (battle_has_status_effect_for_status_window(g_debugchr_selected_unit_id) != 0 || g_debugchr_display_mode == 0)) {
                g_debugchr_thread_refresh_a = one;
                g_debugchr_thread_refresh_b = one;
                g_debugchr_thread_refresh_c = one;
                initialize_event_thread(g_current_event_thread_id - 1,
                    debugchr_text_character_handling_thread);
                battle_store_thread_function_parameters(
                    g_current_event_thread_id - 1,
                    g_menu_descriptor + 0x1e0, 0, 0);
                animation[0] = one;
                animation_second[0] = one;
                animation_third[0] = one;
            child_menu_loop:
                advance_event_thread();
                {
                    s32 render_offset;
                    render_offset = (frame & 1) * 0x4b0;
                    debugchr_render_status_text_primitives(
                        (void*)(render_offset + (s32)render_buffers));
                }
                if (battle_check_thread_running_status(
                        g_current_event_thread_id - 1)
                    != 0) {
                    frame++;
                    goto child_menu_loop;
                }
                animation[0] = 0;
                animation[1] = 0;
                animation[2] = 0;
                g_debugchr_thread_refresh_a = 0;
                g_debugchr_thread_refresh_b = 0;
                g_debugchr_thread_refresh_c = 0;
            }
        }

        if ((*g_debugchr_controller_input & 8) != 0) {
            s16* unit_type_ptr;
            volatile u8* unit_ids;
            volatile u8* chosen_unit;

            comparison = g_debugchr_comparison_index;
            g_sound_effect_id_to_play = 6;
            g_debugchr_status_animation[1] = 7;
            unit_ids = g_debugchr_unit_ids_for_previous;
            comparison ^= 1;
            g_debugchr_comparison_index = comparison;
            chosen_unit = unit_ids + comparison;
            *selected_unit = *chosen_unit;
            selected_unit[-5] = *chosen_unit;
            unit_type_ptr = &g_debugchr_unit_id_801c52e6;
            *unit_type_ptr = *chosen_unit;
            debugchr_load_selected_unit_into_editor();
            battle_copy_active_turn_data_from(
                unit_type_ptr - 5, selected_unit - 5,
                g_debugchr_editor_unit_fields);
            g_debugchr_panel_refresh_a = one;
            g_debugchr_panel_refresh_b = one;
            g_debugchr_panel_refresh_c = one;
        }
        if ((*g_debugchr_controller_input & 4) != 0) {
            register s16* unit_type_ptr __asm__("$16");
            volatile u8* unit_ids;
            volatile u8* chosen_unit;

            comparison = g_debugchr_comparison_index;
            g_sound_effect_id_to_play = 6;
            g_debugchr_status_animation[0] = 7;
            unit_ids = g_debugchr_unit_ids_for_next;
            comparison ^= 1;
            g_debugchr_comparison_index = comparison;
            chosen_unit = unit_ids + comparison;
            *selected_unit = *chosen_unit;
            selected_unit[-5] = *chosen_unit;
            unit_type_ptr = &g_debugchr_unit_id_801c52e6;
            *unit_type_ptr = *chosen_unit;
            debugchr_load_selected_unit_into_editor();
            battle_copy_active_turn_data_from(
                unit_type_ptr - 5, selected_unit - 5,
                g_debugchr_editor_unit_fields);
            g_debugchr_panel_refresh_a = 2;
            g_debugchr_panel_refresh_b = one;
            g_debugchr_panel_refresh_c = one;
        }
    next_frame:
        frame++;
    }

restore_selected_unit: {
    s16* selected_unit_ptr;
    s16* unit_type_ptr;
    s32 selected_value;
    s32 comparison_value;
    s32 unit_ids_or_value;

    unit_ids_or_value = (s32)g_debugchr_unit_ids;
    selected_unit_ptr = &g_debugchr_selected_unit_id;
    selected_value = *(volatile u8*)unit_ids_or_value;
    comparison_value = *(volatile u8*)unit_ids_or_value;
    unit_type_ptr = &g_debugchr_unit_id_801c52e6;
    selected_unit_ptr[0] = selected_value;
    /* Stops GCC folding the next store into a direct global address
     * (+4 bytes without it). */
    __asm__("" : "=r"(selected_unit_ptr) : "0"(selected_unit_ptr));
    selected_unit_ptr[-5] = comparison_value;
    unit_ids_or_value = *(volatile u8*)unit_ids_or_value;
    *unit_type_ptr = unit_ids_or_value;
    selected_unit_ptr -= 5;
    debugchr_load_selected_unit_into_editor();
    battle_copy_active_turn_data_from(
        unit_type_ptr - 5, selected_unit_ptr,
        g_debugchr_editor_unit_fields);
}
}
