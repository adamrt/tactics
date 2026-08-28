#include "psx/gpu.h"
#include "psx/types.h"

extern const char g_card_decimal_format[];
extern u8 g_card_text_color[3];
extern s16 g_card_text_otag_index;
extern s16 g_card_draw_semitrans;
extern u16 g_card_digit_clut;
extern u16 g_card_digit_texture_page;

extern s32 sprintf(char* destination, const char* format, ...);
extern void card_enqueue_textured_quad(RECT* rect, s32 u, s32 v,
    const u8* color, s32 semitrans,
    s32 texture_page, s32 clut,
    s32 otag_index);

u8* card_parse_draw_decimal_number(u8* command) {
    s8 digits[16];
    RECT destination;
    RECT glyph;
    volatile u8 unused_stack[16];
    const u8* color;
    u16 clut;
    s32 destination_y;
    s32 digit_index;
    s32 leading_zeroes;
    s32 column;
    s32 digit;
    char* digit_destination = (char*)digits;
    const char* decimal_format = g_card_decimal_format;
    s32 value;
    /* The pin and every fence below are individually load-bearing (each
     * removal re-verified): the "memory" fences fix the s3/s1 zeroing
     * positions and keep combine from folding `column_count > 0` (a
     * zero-extended lbu) into `beqz`; the target has `blez`. */
    register s32 column_count __asm__("$2");

    __asm__("" : : "r"(digit_destination), "r"(decimal_format));
    digit_index = 0;
    __asm__ volatile("" : : "r"(digit_index) : "memory");
    value = command[9];
    destination_y = command[8];
    clut = g_card_digit_clut;
    __asm__("" : : "r"(value), "r"(destination_y), "r"(clut));
    glyph.x = 0x78;
    glyph.y = 0x10;
    glyph.w = 6;
    glyph.h = 0xb;
    leading_zeroes = command[4] - sprintf(digit_destination, decimal_format, value);
    __asm__("" : : "r"(leading_zeroes) : "memory");
    column_count = *(volatile u8*)&command[4];
    color = g_card_text_color;

    __asm__ volatile("" : : "r"(color) : "memory");
    column = 0;
    if (column_count > 0) {
        do {
            destination.x = command[7] + column * command[5];
            destination.y = destination_y;
            destination.w = glyph.w;
            destination.h = glyph.h;
            if ((s16)leading_zeroes != 0) {
                digit = 0;
                leading_zeroes--;
            } else {
                digit = digits[digit_index] - '0';
                digit_index++;
            }
            if (command[2] < 2) {
                card_enqueue_textured_quad(
                    &destination, glyph.x + glyph.w * digit, glyph.y,
                    color, g_card_draw_semitrans, g_card_digit_texture_page, clut,
                    g_card_text_otag_index);
            }
            column++;
        } while (column < command[4]);
    }
    return command + command[1];
}
