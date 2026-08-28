#include "psx/gpu.h"
#include "psx/types.h"

extern const u8 g_card_cursor_forward_offset_keyframes[];
extern const u8 g_card_cursor_reverse_offset_keyframes[];
extern u16 g_card_cursor_texture_page;
extern u16 g_card_cursor_mode0_foreground_clut;
extern u16 g_card_cursor_mode0_background_clut;
extern u16 g_card_cursor_mode1_foreground_clut;
extern u16 g_card_cursor_mode1_background_clut;

extern s32 card_get_event_speed(void);
extern void card_enqueue_textured_quad(RECT* rect, s32 u, s32 v,
    const u8* color, s32 semitrans,
    s32 texture_page, s32 clut,
    s32 otag_index);

void card_update_and_draw_animated_cursor(const u16* position,
    u16* animation_state_arg, s32 mode) {
    RECT rect;
    u16* animation_state = animation_state_arg;
    s32 reverse;
    u32 state_value;
    s32 frame;
    s32 table_offset;
    s32 x_offset;
    s32 raw_offset;
    s32 threshold;
    u16 foreground_clut;
    u16 background_clut;

    state_value = *animation_state;
    state_value >>= 15;
    reverse = state_value;
    if (mode == 0) {
        if (state_value != 0) {
            *animation_state = 0;
            reverse = 0;
        }
    }
    state_value = reverse;
    if (state_value == 0 && (mode & 1) != 0) {
        *animation_state = 0x8000;
        reverse = 1;
    }

    frame = *animation_state;
    frame &= 0x7f;
    frame *= card_get_event_speed();
    state_value = reverse;
    if (state_value == 0) {
        goto forward_clamp;
    }
    state_value = frame < 0x25;
    if (state_value != 0) {
        goto select_offset;
    }
    frame = 0x24;
    goto select_offset;
forward_clamp:
    state_value = frame < 0x2f;
    if (state_value != 0) {
        goto select_offset;
    }
    frame = 0;
select_offset:
    state_value = reverse;
    if (state_value != 0) {
        table_offset = 0;
        threshold = (s8)g_card_cursor_reverse_offset_keyframes[table_offset];
        while (threshold < frame) {
            table_offset += 2;
            threshold = (s8)g_card_cursor_reverse_offset_keyframes[table_offset];
        }
        raw_offset = g_card_cursor_reverse_offset_keyframes[table_offset + 1];
    } else {
        table_offset = 0;
        threshold = (s8)g_card_cursor_forward_offset_keyframes[table_offset];
        while (threshold < frame) {
            table_offset += 2;
            threshold = (s8)g_card_cursor_forward_offset_keyframes[table_offset];
        }
        raw_offset = g_card_cursor_forward_offset_keyframes[table_offset + 1];
    }
    x_offset = (s8)raw_offset;

    frame += card_get_event_speed();
    state_value = reverse;
    if (state_value == 0) {
        goto forward_update;
    }
    state_value = frame < 0x25;
    if (state_value == 0) {
        goto finish_update;
    }
    goto increment_state;
forward_update:
    state_value = frame < 0x2f;
    if (state_value == 0) {
        goto clear_state;
    }
increment_state:
    (*animation_state)++;
    goto finish_update;
clear_state:
    *animation_state = 0;
finish_update:

    if (mode != 0) {
        foreground_clut = g_card_cursor_mode1_foreground_clut;
        background_clut = g_card_cursor_mode1_background_clut;
    } else {
        foreground_clut = g_card_cursor_mode0_foreground_clut;
        background_clut = g_card_cursor_mode0_background_clut;
    }

    rect.x = x_offset + position[0] - 2;
    rect.y = position[1];
    rect.w = 0x10;
    rect.h = 0x10;
    card_enqueue_textured_quad(&rect, 0xa8, 0, 0, 0, g_card_cursor_texture_page,
        foreground_clut, 0x3c);

    rect.x += 2;
    rect.y += 2;
    card_enqueue_textured_quad(&rect, 0xb8, 0, 0, 1, 0x5f,
        background_clut, 0x3b);
}
