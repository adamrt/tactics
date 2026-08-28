#include "psx/gpu.h"
#include "psx/types.h"
#define FIELD(base, type, offset) (*(type*)((u8*)(base) + (offset)))
extern u8* g_event_threads;
extern s32 g_require_indicator_packet_index[2];
extern s32 g_require_indicator_brightness[2];
extern s32 g_require_indicator_fade_work[2];
extern s32 g_require_indicator_state[2];
extern u8 g_require_primitive_tail_template[];
extern u8 g_require_thread_indicator_packets[];
extern s32 require_is_event_thread_running(s32 thread_id);
extern void submit_primitive(void* primitive);
void require_render_thread_status_indicators(void) {
    s32* fade_work[1];
    s32 packet_bank_offset;
    s16 background_y;
    register s32* state;
    s32* thread;
    s32 draw_y;
    register s32 brightness;
    s32 indicator_state;
    s32 panel_offset;
    s32 line;
    s32 panel;
    s32 active_thread_id;
    s32 left_offset;
    volatile u8* brightness_ptr;
    s32 y;
    s32 right_offset;
    void* event_thread;
    void* candidate;
    void* tile;
    s32* fade_cursor;
    void* right_tile;
    void* packet;
    register void* left_packet __asm__("$17");
    void* right_packet;
    s32* packet_index;
    active_thread_id = 0;
    if (require_is_event_thread_running(8) != 0) {
        event_thread = g_event_threads;
        if (FIELD(event_thread, s32, 0x204c) == 0x39) {
            thread = FIELD(event_thread, s32*, 0x2000);
            active_thread_id = (*thread == 0) * 8;
        }
    }
    if (require_is_event_thread_running(7) != 0) {
        event_thread = g_event_threads;
        if (FIELD(event_thread, s32, 0x1c4c) == 0x39) {
            candidate = FIELD(event_thread, void*, 0x1c00);
            if (FIELD(candidate, s32, 0) == 0) {
                active_thread_id = 7;
                thread = candidate;
            }
        }
    }
    if (active_thread_id != 0) {
        if ((FIELD(thread, s32, 4) == 0x90) && !(FIELD(thread, s32, 8) & 0x80)) {
            g_require_indicator_state[0] = 2;
            y = 1;
            goto set_second_state;
        }
        if ((FIELD(thread, s32, 4) == 0) && !(FIELD(thread, s32, 8) & 0x80)) {
            g_require_indicator_state[0] = 1;
            y = 2;
            goto set_second_state;
        }
        goto update_first_state;
    }
update_first_state:
    if (g_require_indicator_state[0] == 1) {
        g_require_indicator_state[0] = 2;
    }
    if (g_require_indicator_state[1] != 1) {
        panel = 0;
        goto render_panels;
    }
    y = 2;
set_second_state:
    g_require_indicator_state[1] = y;
    panel = 0;
render_panels:
    fade_work[0] = g_require_indicator_fade_work;
    panel_offset = 0;
    brightness_ptr = (u8*)g_require_indicator_brightness;
    packet_bank_offset = 0;
    do {
        packet_index = (s32*)((u8*)g_require_indicator_packet_index + panel_offset);
        *packet_index ^= 1;
        packet = g_require_thread_indicator_packets + packet_bank_offset + *packet_index * 0x13c;
        SetDrawMode(packet, 0, 0,
            GetTPage(0, 2, 0x3c0, 0x100) & 0xffff,
            (RECT*)g_require_primitive_tail_template);
        tile = packet + 0xc;
        SetTile(tile);
        FIELD(packet, u8, 0x10) = 0;
        FIELD(packet, u8, 0x11) = 0;
        FIELD(packet, u8, 0x12) = 0;
        SetSemiTrans(tile, 1);
        background_y = 0xb2;
        if (panel == 0) {
            background_y = 0x23;
        }
        line = 0;
        right_offset = 0xac;
        left_packet = packet;
        left_offset = 0x1c;
        FIELD(packet, s16, 0x14) = 0x80;
        FIELD(packet, s16, 0x16) = background_y;
        FIELD(packet, s16, 0x18) = 0x100;
        FIELD(packet, s16, 0x1a) = 0x32;
    line_loop:
        tile = packet + left_offset;
        SetTile(tile);
        FIELD(left_packet, u8, 0x20) = 0;
        FIELD(left_packet, u8, 0x21) = 0;
        FIELD(left_packet, u8, 0x22) = 0;
        SetSemiTrans(tile, 1);
        y = 0xa9;
        FIELD(left_packet, s16, 0x28) = 0x100;
        FIELD(left_packet, s16, 0x2a) = 1;
        if (panel == 0) {
            y = 0x1a;
        }
        right_tile = packet + right_offset;
        FIELD(left_packet, s16, 0x24) = 0x80;
        FIELD(left_packet, s16, 0x26) = y + line;
        SetTile(right_tile);
        FIELD(left_packet, u8, 0xb0) = 0;
        FIELD(left_packet, u8, 0xb1) = 0;
        FIELD(left_packet, u8, 0xb2) = 0;
        SetSemiTrans(right_tile, 1);
        y = 0xe4;
        FIELD(left_packet, s16, 0xb8) = 0x100;
        FIELD(left_packet, s16, 0xba) = 1;
        if (panel == 0) {
            y = 0x55;
        }
        right_offset += 0x10;
        FIELD(left_packet, s16, 0xb4) = 0x80;
        FIELD(left_packet, s16, 0xb6) = y + line;
        left_packet += 0x10;
        line++;
        left_offset += 0x10;
        if (line < 9) {
            goto line_loop;
        }
        indicator_state = *(s32*)((u8*)g_require_indicator_state + panel_offset);
        if (indicator_state == 0) {
            FIELD(packet, u8, 0x10) = 0;
            FIELD(packet, u8, 0x11) = 0;
            FIELD(packet, u8, 0x12) = 0;
        } else {
            if (indicator_state == 1) {
                s32* fade_in_word;
                /* Preserve the retail compiler's temporary address register. */
                __asm__ volatile(
                    "lui $8,%%hi(g_require_indicator_brightness)\n"
                    "addiu $8,$8,%%lo(g_require_indicator_brightness)\n"
                    "addu %0,%1,$8"
                    : "=r"(fade_in_word)
                    : "r"(panel_offset));
                brightness = *fade_in_word;
                if (brightness < 0x78) {
                    *fade_in_word = brightness + 0xc;
                }
            }
            state = (s32*)((u8*)g_require_indicator_state + panel_offset);
            if (*state == 2) {
                s32* fade_out_word;
                /* Preserve the retail compiler's temporary address register. */
                __asm__ volatile(
                    "lui $8,%%hi(g_require_indicator_brightness)\n"
                    "addiu $8,$8,%%lo(g_require_indicator_brightness)\n"
                    "addu %0,%1,$8"
                    : "=r"(fade_out_word)
                    : "r"(panel_offset));
                if (*fade_out_word != 0) {
                    *fade_out_word -= 0xc;
                } else {
                    *state = 0;
                }
            }
            FIELD(packet, u8, 0x10) = *(u8*)brightness_ptr;
            line = 0;
            fade_cursor = fade_work[0];
            FIELD(packet, u8, 0x11) = *(u8*)brightness_ptr;
            left_offset = 0xac;
            FIELD(packet, u8, 0x12) = *(u8*)brightness_ptr;
            left_packet = packet;
            *fade_cursor = *(s32*)brightness_ptr;
            do {
                if (*fade_cursor != 0) {
                    *fade_cursor -= 0xc;
                }
                draw_y = (8 - line) * 0x10;
                right_packet = (void*)(draw_y + (s32)packet);
                FIELD(right_packet, u8, 0x20) = *(u8*)fade_cursor;
                FIELD(right_packet, u8, 0x21) = *(u8*)fade_cursor;
                FIELD(right_packet, u8, 0x22) = *(u8*)fade_cursor;
                draw_y += 0x1c;
                FIELD(left_packet, u8, 0xb0) = *(u8*)(right_packet = fade_cursor);
                FIELD(left_packet, u8, 0xb1) = *(u8*)right_packet;
                FIELD(left_packet, u8, 0xb2) = *(u8*)right_packet;
                submit_primitive(packet + draw_y);
                line++;
                submit_primitive(packet + left_offset);
                left_offset += 0x10;
                left_packet += 0x10;
            } while (line < 9);
            submit_primitive(packet + 0xc);
            submit_primitive(packet);
        }
        panel_offset += 4;
        brightness_ptr += 4;
        panel++;
        fade_work[0]++;
        packet_bank_offset += 0x278;
    } while (panel < 2);
}
