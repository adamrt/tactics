#include "psx/types.h"

#define U8_AT(base, offset)  (*(u8*)((base) + (offset)))
#define S16_AT(base, offset) (*(s16*)((base) + (offset)))
#define U16_AT(base, offset) (*(u16*)((base) + (offset)))
#define S32_AT(base, offset) (*(s32*)((base) + (offset)))

extern void set_current_thread_task_id(s32 task_id);
extern s32* battle_get_controller_input_pointer(s32 controller);
extern void initialize_menu_draw_mode_packet(void* state, s32 value);
extern void battle_initialize_numeric_display_frame_primitives(void* source, void* destination);
extern void require_initialize_portrait_primitive_tail(void* primitive);
extern void battle_initialize_semitransparent_menu_sprt(void* primitive);
extern void configure_textured_primitive_geometry(void* primitive, const void* data,
    const void* text, const void* descriptor);
extern void world_copy_bytes(void* destination, const void* source, s32 size);
extern void clear_menu_render_buffer(void* buffer, s32 size);
extern void world_set_menu_text_origin(s32 x, s32 y);
extern void require_render_signed_decimal_entries(s32 base, void* entries,
    void* output, s32 count);
extern void render_numeric_display_entries(s32 base, void* entries, void* output,
    s32 count);
extern void LoadImage(void* rect, void* source);
extern void require_configure_scaled_draw_area_packets(
    void* packets, const void* geometry, s32 buffer, s32 frame_offset,
    void* thread);
extern void SetDrawOffset(void* destination, void* position);
extern void require_initialize_menu_primitive_colors(void* primitives,
    void* thread);
extern void submit_primitive(void* primitive);
extern void battle_submit_numeric_display_frame_primitives(void* primitive);
extern void advance_event_thread(void);
extern s32 battle_get_third_thread_parameter(void);
extern void stop_current_event_thread(void);

extern s32 g_current_event_thread_id;
extern u8* g_event_threads;
extern s32 g_event_mode;
extern s32 g_menu_text_origin_x;
extern s32 g_gpu_frame_counter;
extern s32* g_require_controller_input;
extern s16 g_require_draw_area_x;

extern u8 g_require_numeric_state_a[];
extern u8 g_require_numeric_state_b[];
extern u8 g_require_numeric_text_a[];
extern u8 g_require_numeric_text_b[];
extern u8 g_require_numeric_entries_a[];
extern u8 g_require_numeric_entries_b[];
extern u8 g_require_numeric_entries_c[];
extern u8 g_require_numeric_entries_d[];
extern u8 g_require_numeric_entries_e[];
extern u8 g_require_numeric_entries_f[];
extern u8 g_require_numeric_descriptor_a[];
extern u8 g_require_numeric_descriptor_b[];
extern u8 g_require_numeric_table[];
extern u8 g_require_numeric_geometry[];
extern u8 g_require_numeric_texture[];

void require_run_numeric_editor_thread(void) {
    typedef struct StackPointer {
        u8* value;
        s32 padding;
    } StackPointer;
    u8* thread;
    u8* state;
    u8* text;
    u8* entries;
    s32 frame;
    register s32 i asm("$17");
    register s32 twelve;
    register u8* selected_upload_c asm("$8");
    StackPointer stack_pointers[4];
#define state_base stack_pointers[0].value
#define upload_a   (*(u8* volatile*)&stack_pointers[1].value)
#define upload_b   (*(u8* volatile*)&stack_pointers[2].value)
#define upload_c   (*(u8* volatile*)&stack_pointers[3].value)

    set_current_thread_task_id(0x3b);
    thread = *(u8**)((g_current_event_thread_id << 10) + (s32)g_event_threads);
    g_require_controller_input = battle_get_controller_input_pointer(0) + 1;

    if (g_current_event_thread_id == 0xc) {
        state = g_require_numeric_state_a;
        text = g_require_numeric_text_a;
        selected_upload_c = g_require_numeric_entries_a;
        upload_a = selected_upload_c;
        selected_upload_c = g_require_numeric_entries_b;
        upload_b = selected_upload_c;
        selected_upload_c = g_require_numeric_entries_c;
        entries = g_require_numeric_descriptor_a;
        *(volatile s32*)&stack_pointers[0] = (s32)state;
        goto numeric_buffers_selected;
    }
    state = g_require_numeric_state_b;
    text = g_require_numeric_text_b;
    selected_upload_c = g_require_numeric_entries_d;
    upload_a = selected_upload_c;
    selected_upload_c = g_require_numeric_entries_e;
    upload_b = selected_upload_c;
    selected_upload_c = g_require_numeric_entries_f;
    entries = g_require_numeric_descriptor_b;
    state_base = g_require_numeric_state_b;
numeric_buffers_selected:
    upload_c = selected_upload_c;

    initialize_menu_draw_mode_packet(state, 0);
    initialize_menu_draw_mode_packet(state + 0xc, 2);
    initialize_menu_draw_mode_packet(state + 0x18, 1);
    battle_initialize_numeric_display_frame_primitives(g_require_numeric_table,
        state + 0x18c);
    require_initialize_portrait_primitive_tail(state + 0x298);

    i = 0;
    {
        u8* descriptor = g_require_numeric_texture;
        u8* primitive;
        frame = 0x24;
        do {
            primitive = state + frame;
            battle_initialize_semitransparent_menu_sprt(primitive);
            configure_textured_primitive_geometry(primitive, g_require_numeric_geometry,
                g_require_numeric_table, descriptor);
            descriptor += 0xc;
            i++;
            frame += 0x14;
        } while (i < 0x12);
    }

    if (g_current_event_thread_id != 0xc) {
        s32 first;
        register s32 second asm("$3");
        first = U8_AT(state, 0x149);
        second = U8_AT(state, 0x171);
        first += 0x4c;
        U8_AT(state, 0x149) = first;
        first = U8_AT(state, 0x15d);
        second += 0x4c;
        U8_AT(state, 0x171) = second;
        first += 0x4c;
        U8_AT(state, 0x15d) = first;
    }
    S16_AT(state, 0xfa) = 0x7d7c;
    world_copy_bytes(state + 0x2c0, state, 0x2c0);

    frame = 0;
    {
        register s32* origin asm("$20") = &g_menu_text_origin_x;
        twelve = 0xc;
        for (;;) {
            s32 offset;
            s16 color_value;
            s32 parity;
            s32 frame_offset;
            u8* buffer;
            register u8* selected_state_base asm("$8");
            u8* draw_packets;

            parity = frame & 1;
            frame_offset = parity << 1;
            frame_offset += parity;
            frame_offset <<= 2;
            frame_offset -= parity;
            selected_state_base = state_base;
            frame_offset <<= 6;
            buffer = selected_state_base + frame_offset;
            draw_packets = buffer + 0x298;

            if (frame == 0 || S32_AT(thread, 0xc) != 0) {
                clear_menu_render_buffer(text, 0x918);
                *origin = 0x14;
                world_set_menu_text_origin(0, 0);
                if (g_current_event_thread_id != twelve)
                    require_render_signed_decimal_entries((s32)text, entries,
                        (u8*)origin - 8, 3);
                else
                    render_numeric_display_entries((s32)text, entries,
                        (u8*)origin - 8, 3);
                *origin = 0x40;
                world_set_menu_text_origin(0, 0);
                if (g_current_event_thread_id != twelve)
                    require_render_signed_decimal_entries((s32)(text + 0x168),
                        entries + 0x24, (u8*)origin - 8, 4);
                else
                    render_numeric_display_entries((s32)(text + 0x168), entries + 0x24,
                        (u8*)origin - 8, 4);
                *origin = 0x64;
                world_set_menu_text_origin(0, 0);
                if (g_current_event_thread_id != twelve)
                    require_render_signed_decimal_entries((s32)(text + 0x468),
                        entries + 0x54, (u8*)origin - 8, 8);
                else
                    render_numeric_display_entries((s32)(text + 0x468), entries + 0x54,
                        (u8*)origin - 8, 8);
                LoadImage(upload_a, text);
                LoadImage(upload_b, text + 0x168);
                LoadImage(upload_c, text + 0x468);
            }

            {
                s32 scaled;
                s32 different;
                scaled = g_gpu_frame_counter * 0xf0;
                different = scaled ^ 0xf0;
                different = (u32)different > 0;
                different = -different;
                g_require_draw_area_x = different & 0xf0;
                require_configure_scaled_draw_area_packets(buffer + 0x298,
                    g_require_numeric_table + 8, frame, scaled, thread);
            }
            {
                u8* primitive = buffer + 0x278;
                register s32 x asm("$2") = U16_AT(thread, 0);
                s32 draw_area = (u16)g_require_draw_area_x;
                x -= 0x80;
                S16_AT(buffer, 0x284) = x;
                x = U16_AT(thread, 4);
                S16_AT(buffer, 0x286) = x + draw_area;
                SetDrawOffset(primitive, buffer + 0x284);
            }
            {
                u8* primitive = buffer + 0x288;
                u8* position = buffer + 0x294;
                s32 draw_area = (u16)g_require_draw_area_x;
                s32 x = -0x80;
                S16_AT(buffer, 0x294) = x;
                U16_AT(buffer, 0x296) = draw_area;
                SetDrawOffset(primitive, position);
            }

            i = 0x11;
            if (S32_AT(thread, 0x10) == 1 || g_event_mode == 1) {
                s32 palette_color = 0x7d3c;
                u8* primitive = buffer + 0x154;
                do {
                    S16_AT(primitive, 0x32) = palette_color;
                    i--;
                    primitive -= 0x14;
                } while (i >= 0);
                S16_AT(buffer, 0xfa) = 0x7ebc;
                color_value = 0x7f7d;
            } else {
                s32 palette_color = 0x7c3c;
                u8* primitive = buffer + 0x154;
                do {
                    S16_AT(primitive, 0x32) = palette_color;
                    i--;
                    primitive -= 0x14;
                } while (i >= 0);
                S16_AT(buffer, 0xfa) = 0x7d7c;
                color_value = 0x7ffc;
            }
            S16_AT(buffer, 0x14a) = color_value;
            S16_AT(buffer, 0x15e) = color_value;
            S16_AT(buffer, 0x172) = color_value;
            __asm__ volatile("" : : : "memory");
            require_initialize_menu_primitive_colors(buffer + 0x18c, thread);

            i = 0;
            if (frame < 0xd)
                submit_primitive(buffer + 0x2a4);
            submit_primitive(buffer + 0x288);
            offset = 0x24;
            do {
                submit_primitive(buffer + offset);
                i++;
                offset += 0x14;
            } while (i < 0xe);
            submit_primitive(buffer + 0x178);
            submit_primitive(buffer);
            if (i < 0x11) {
                offset = i * 0x14 + 0x24;
                do {
                    submit_primitive(buffer + offset);
                    i++;
                    offset += 0x14;
                } while (i < 0x11);
            }
            if (g_current_event_thread_id == twelve)
                submit_primitive(buffer + 0xc);
            else
                submit_primitive(buffer + 0x18);
            battle_submit_numeric_display_frame_primitives(buffer + 0x18c);
            submit_primitive(buffer + 0x278);
            if (frame < 0xd)
                submit_primitive(buffer + 0x298);
            advance_event_thread();
            {
                s32 should_stop = battle_get_third_thread_parameter();
                __asm__("" : "=r"(frame) : "0"(frame), "r"(should_stop));
                frame++;
                if (should_stop != 0)
                    break;
            }
        }
    }
    advance_event_thread();
    stop_current_event_thread();
#undef state_base
#undef upload_a
#undef upload_b
#undef upload_c
}
