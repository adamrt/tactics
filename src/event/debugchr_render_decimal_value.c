#include "psx/types.h"

typedef struct DebugChrGlyph {
    s16 source_x;
    s16 source_y;
    s16 width;
    s16 height;
} DebugChrGlyph;

typedef struct DebugChrTextPosition {
    u16 x;
    u16 y;
    u8 unknown_04[4];
    u16 unknown_0a;
    s32 pixel_adjustment;
} DebugChrTextPosition;

extern void* g_battle_text_pointers;
extern DebugChrGlyph g_debugchr_decimal_glyph;

extern void blit_text_glyph(void* text, void* pixels, DebugChrGlyph* glyph,
    DebugChrTextPosition* position);

void debugchr_render_decimal_value(s32 value, s32 flags, void* pixels,
    DebugChrTextPosition* position) {
    s32 current_value = value;
    s32 render_flags = flags;
    void* render_pixels = pixels;
    DebugChrTextPosition* render_position = position;
    s32 saved_color;
    register s32 digit_index __asm__("$18");
    register DebugChrGlyph* glyph __asm__("$21");
    register s32 updated_flags __asm__("$2");
    register s32 minimum_digits __asm__("$5");
    register s32 scratch __asm__("$3");
    volatile u32 stack_padding[2];
    s32 field_digits;
    s32 quotient;

    __asm__("" : : "r"(render_pixels));
    __asm__("" : : "r"(render_position));

    saved_color = render_position->pixel_adjustment;
    render_position->pixel_adjustment = 0;

    if ((render_flags & 0x0200) != 0) {
        if (current_value == 100) {
            updated_flags = render_flags & 0xff00;
            render_flags = updated_flags + 3;
        }
    }

    if ((render_flags & 0x8000) != 0) {
        render_position->x -= 2;
        g_debugchr_decimal_glyph.source_x = 0xb4;
        blit_text_glyph(g_battle_text_pointers, render_pixels,
            &g_debugchr_decimal_glyph, render_position);
        render_position->x += 7;
    }

    if ((render_flags & 0x0100) != 0) {
        g_debugchr_decimal_glyph.source_x = 0x78;
        g_debugchr_decimal_glyph.source_y = 0x1a;
        g_debugchr_decimal_glyph.height = 4;
        render_position->y += 3;
        blit_text_glyph(g_battle_text_pointers, render_pixels,
            &g_debugchr_decimal_glyph, render_position);
        render_position->x += 7;
        render_position->y -= 3;
        g_debugchr_decimal_glyph.source_y = 0x10;
        g_debugchr_decimal_glyph.height = 0x0a;
    }

    render_position->pixel_adjustment = saved_color;

    if ((render_flags & 0x0800) != 0) {
        g_debugchr_decimal_glyph.source_x = 0xba;
        if (current_value == 0) {
            if ((render_flags & 0x0f) == 4) {
                render_position->x += 10;
            } else {
                render_position->x += 5;
            }
        }
        blit_text_glyph(g_battle_text_pointers, render_pixels,
            &g_debugchr_decimal_glyph, render_position);
        render_position->x += 5;
        if (current_value == 0) {
            return;
        }
    }

    saved_color = render_flags & 0x0400;
    if (saved_color != 0) {
        g_debugchr_decimal_glyph.source_x = 0xc8;
        blit_text_glyph(g_battle_text_pointers, render_pixels,
            &g_debugchr_decimal_glyph, render_position);
        render_position->x += 5;
    }

    field_digits = render_flags & 0x0f;
    if ((render_flags & 0x2000) != 0) {
        field_digits = 3;
    }
    if (saved_color != 0) {
        field_digits--;
    }
    updated_flags = render_flags & 0x0800;
    minimum_digits = 1;
    if (updated_flags != 0) {
        field_digits--;
    }

    scratch = render_flags & 0x0f;
    if (current_value < 10) {
        __asm__("" : : : "$5");
        minimum_digits = 1;
    }
    digit_index = 0;
    if (scratch != 1) {
        updated_flags = field_digits - minimum_digits;
        __asm__("" : : "r"(updated_flags));
        render_position->x += updated_flags * 5;
    }

    if ((render_flags & 0xff) > 0) {
        glyph = &g_debugchr_decimal_glyph;
        do {
            quotient = current_value / 10;
            scratch = quotient * 4;
            scratch = current_value - ((scratch + quotient) * 2);
            glyph->source_x = (scratch * 6) + 0x78;
            blit_text_glyph(g_battle_text_pointers, render_pixels, glyph,
                render_position);
            render_position->x -= 5;
            current_value = quotient;
            if (((render_flags & 0x4000) != 0) || (current_value != 0)) {
                digit_index++;
                if (digit_index < (render_flags & 0xff)) {
                    continue;
                }
            }
            break;
        } while (1);
    }

    render_position->pixel_adjustment = 0;
}
