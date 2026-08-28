#include "psx/gpu.h"
#include "psx/types.h"

/* Field access relative to a POLY_GT4 cursor that the retail build keeps
 * pointing 0x2a bytes into the primitive (its b3 byte). */
#define FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))

typedef struct EtcGraphic {
    const char* path;
    s32 lba;
    s32 size;
    void* framebuffer_rect;
    s16* dimensions;
    void* unused_14;
    void* unused_18;
    s32 texture_mode;
} EtcGraphic;

extern EtcGraphic g_etc_graphics[];
extern void submit_primitive(void* primitive);

/* Build the 2x2 POLY_GT4 grid that shows a chapter title graphic. Each
 * dimension row is six s16 values: x, y, w, h, u-ish x offset, y offset. */
void etc_build_chapter_graphic_polygons(s32 graphic_id, s32 fade,
    s32 dimension_set, s32 layer,
    volatile s32 primitives, s32 color) {
    /* Locals the retail build keeps on the stack, one word apart. */
    volatile struct {
        s32 layer;
        s32 pad14;
        s32 dimensions;
        s32 pad1c;
        s32 texture_mode;
        s32 pad24;
        s32 tpage_bits;
        s32 pad2c;
        s32 tpage_shifted;
        s32 pad34;
        s32 tpage_right_alt;
        s32 pad3c;
        s32 tpage_right;
        s32 pad44;
        s32 tpage_left_alt;
        s32 pad4c;
        s32 tpage_left;
    } stack;
    register s32 row_height __asm__("$3");
    s16 clut;
    s32 clip_base;
    register s32 dimension_offset __asm__("$4");
    register s32 clip_end __asm__("$4");
    s32 fade_right;
    register s32 scratch __asm__("$8");
    s32 tpage_shifted;
    s32 value;
    s32 last_primitive;
    register s32 clip_height __asm__("$6");
    register s32 dimension_index __asm__("$19");
    register s32 one __asm__("$22");
    s32 row;
    s32 poly;
    s32 row_offset;
    register s32 column __asm__("$23");
    s32 y_offset;
    register s32 y_bottom __asm__("$3");
    void* dims_faded;
    void* dims;
    void* dims_clipped;
    void* fields;

    dimension_index = dimension_set;
    row = 0;
    stack.layer = layer;
    scratch = g_etc_graphics[graphic_id].dimensions;
    stack.dimensions = scratch;
    dimension_offset = g_etc_graphics[graphic_id].texture_mode;
    poly = primitives;
    scratch = dimension_offset & 3;
    stack.tpage_bits = scratch;
    tpage_shifted = scratch << 9;
    stack.tpage_shifted = tpage_shifted;
    stack.texture_mode = dimension_offset;
    stack.tpage_right_alt = tpage_shifted | 0x86;
    one = 1;
    do {
        column = 0;
        row_offset = 0;
        scratch = stack.tpage_bits;
        fields = poly + 0x2A;
        value = scratch << 7;
        stack.tpage_right = (scratch = value | 0x26);
        scratch = stack.tpage_shifted;
        stack.tpage_left = value | 0x46;
        stack.tpage_left_alt = scratch | 0x106;
    next_column:
        SetPolyGT4(poly);
        SetShadeTex(poly, 0);
        SetSemiTrans(poly, 1);
        FIELD(fields, u8*, -0x1E) = 0U;
        FIELD(fields, u8*, -0x1D) = 0U;
        FIELD(fields, s8*, -0x12) = one;
        FIELD(fields, u8*, -0x11) = 0U;
        FIELD(fields, u8*, -6) = 0U;
        FIELD(fields, s8*, -5) = one;
        FIELD(fields, s8*, 6) = one;
        FIELD(fields, s8*, 7) = one;
        FIELD(fields, s16*, -0x22) = 0;
        FIELD(fields, s16*, -0x20) = 0;
        FIELD(fields, s16*, -0x16) = 0;
        FIELD(fields, s16*, -0x14) = 0;
        FIELD(fields, s16*, -0xA) = 0;
        FIELD(fields, s16*, -8) = 0;
        FIELD(fields, s16*, 2) = 0;
        FIELD(fields, s16*, 4) = 0;
        if (column != 0) {
            if ((GetGraphType() == one) || (GetGraphType() == 2)) {
                FIELD(fields, u16*, -0x10) = *(volatile u16*)&stack.tpage_right_alt;
            } else {
                FIELD(fields, u16*, -0x10) = *(volatile u16*)&stack.tpage_right;
            }
        } else if ((GetGraphType() == one) || (GetGraphType() == 2)) {
            FIELD(fields, u16*, -0x10) = *(volatile u16*)&stack.tpage_left_alt;
        } else {
            FIELD(fields, u16*, -0x10) = *(volatile u16*)&stack.tpage_left;
        }
        clut = 0x7F80;
        scratch = stack.texture_mode;
        if (scratch == 0) {
            clut = 0xFDB;
        }
        FIELD(fields, s16*, -0x1C) = clut;
        if (row == 0) {
            scratch = stack.layer;
            dimension_offset = dimension_index << 1;
            if (scratch != 0) {
                dimension_offset += dimension_index;
                scratch = stack.dimensions;
                dimension_offset <<= 2;
                dimension_offset += scratch;
                dims_faded = row_offset + dimension_offset;
                FIELD(fields, u8*, -0x1E) = (u8)((FIELD(dims_faded, u8*, 0) + FIELD(dims_faded, u8*, 4)) - fade);
                FIELD(fields, u8*, -0x1D) = (u8)FIELD(dims_faded, u8*, 2);
                FIELD(fields, s8*, -0x12) = (s8)(FIELD(dims_faded, u8*, 0) + FIELD(dims_faded, u8*, 4));
                FIELD(fields, u8*, -0x11) = (u8)FIELD(dims_faded, u8*, 2);
                FIELD(fields, u8*, -6) = (u8)((FIELD(dims_faded, u8*, 0) + FIELD(dims_faded, u8*, 4)) - fade);
                FIELD(fields, s8*, -5) = (s8)(FIELD(dims_faded, u8*, 2) + FIELD(dims_faded, u8*, 6));
                FIELD(fields, s8*, 6) = (s8)(FIELD(dims_faded, u8*, 0) + FIELD(dims_faded, u8*, 4));
                FIELD(fields, s8*, 7) = (s8)(FIELD(dims_faded, u8*, 2) + FIELD(dims_faded, u8*, 6));
                FIELD(fields, s16*, -0x22) = (s16)(((FIELD(dims_faded, u16*, 8) + FIELD(dims_faded, u16*, 4)) - fade) + 0x100);
                FIELD(fields, s16*, -0x20) = (s16)(FIELD(dims_faded, u16*, 0xA) + 0x80);
                FIELD(fields, s16*, -0x16) = (s16)(FIELD(dims_faded, u16*, 8) + FIELD(dims_faded, u16*, 4) + 0x100);
                FIELD(fields, s16*, -0x14) = (s16)(FIELD(dims_faded, u16*, 0xA) + 0x80);
                FIELD(fields, s16*, -0xA) = (s16)(((FIELD(dims_faded, u16*, 8) + FIELD(dims_faded, u16*, 4)) - fade) + 0x100);
                FIELD(fields, s16*, -8) = (s16)(FIELD(dims_faded, u16*, 0xA) + (FIELD(dims_faded, u16*, 6) + 0x80));
                FIELD(fields, s16*, 2) = (s16)(FIELD(dims_faded, u16*, 8) + FIELD(dims_faded, u16*, 4) + 0x100);
                y_offset = FIELD(dims_faded, u16*, 6);
                y_bottom = FIELD(dims_faded, u16*, 0xA);
                FIELD(fields, s8*, -0x26) = (s8)color;
                FIELD(fields, s8*, -0x25) = (s8)color;
                FIELD(fields, s8*, -0x24) = (s8)color;
                FIELD(fields, s8*, -0x1A) = (s8)color;
                FIELD(fields, s8*, -0x19) = (s8)color;
                FIELD(fields, s8*, -0x18) = (s8)color;
                FIELD(fields, s8*, -0xE) = (s8)color;
                FIELD(fields, s8*, -0xD) = (s8)color;
                FIELD(fields, s8*, -0xC) = (s8)color;
                goto finish_bottom_row;
            }
            dimension_offset += dimension_index;
            scratch = stack.dimensions;
            dimension_offset <<= 2;
            dimension_offset += scratch;
            dims = row_offset + dimension_offset;
            FIELD(fields, u8*, -0x1E) = (u8)FIELD(dims, u8*, 0);
            FIELD(fields, u8*, -0x1D) = (u8)FIELD(dims, u8*, 2);
            FIELD(fields, s8*, -0x12) = (s8)(FIELD(dims, u8*, 0) + fade);
            FIELD(fields, u8*, -0x11) = (u8)FIELD(dims, u8*, 2);
            FIELD(fields, u8*, -6) = (u8)FIELD(dims, u8*, 0);
            FIELD(fields, s8*, -5) = (s8)(FIELD(dims, u8*, 2) + FIELD(dims, u8*, 6));
            FIELD(fields, s8*, 6) = (s8)(FIELD(dims, u8*, 0) + fade);
            FIELD(fields, s8*, 7) = (s8)(FIELD(dims, u8*, 2) + FIELD(dims, u8*, 6));
            FIELD(fields, s16*, -0x22) = (s16)(FIELD(dims, u16*, 8) + 0x100);
            FIELD(fields, s16*, -0x20) = (s16)(FIELD(dims, u16*, 0xA) + 0x80);
            fade_right = fade + 0x100;
            FIELD(fields, s16*, -0x16) = (s16)(FIELD(dims, u16*, 8) + fade_right);
            FIELD(fields, s16*, -0x14) = (s16)(FIELD(dims, u16*, 0xA) + 0x80);
            FIELD(fields, s16*, -0xA) = (s16)(FIELD(dims, u16*, 8) + 0x100);
            FIELD(fields, s16*, -8) = (s16)(FIELD(dims, u16*, 0xA) + (FIELD(dims, u16*, 6) + 0x80));
            FIELD(fields, s16*, 2) = (s16)(FIELD(dims, u16*, 8) + fade_right);
            FIELD(fields, s16*, 4) = (s16)(FIELD(dims, u16*, 0xA) + (FIELD(dims, u16*, 6) + 0x80));
            __asm__ volatile("" : : : "memory");
            FIELD(fields, s8*, -0x26) = (s8)color;
            FIELD(fields, s8*, -0x25) = (s8)color;
            FIELD(fields, s8*, -0x24) = (s8)color;
            FIELD(fields, s8*, -0x1A) = (s8)color;
            FIELD(fields, s8*, -0x19) = (s8)color;
            FIELD(fields, s8*, -0x18) = (s8)color;
            FIELD(fields, s8*, -0xE) = (s8)color;
            FIELD(fields, s8*, -0xD) = (s8)color;
            FIELD(fields, s8*, -0xC) = (s8)color;
            FIELD(fields, s8*, -2) = (s8)color;
            FIELD(fields, s8*, -1) = (s8)color;
            FIELD(fields, s8*, 0) = (s8)color;
        } else if (row == one) {
            scratch = stack.dimensions;
            dims_clipped = row_offset + ((dimension_index * 0xC) + scratch);
            row_height = FIELD(dims_clipped, s16*, 4);
            clip_height = row_height < (fade + 0x20)
                ? row_height - fade
                : 0x20;
            clip_base = clip_height - 0x100;
            scratch = stack.layer;
            if (scratch != 0) {
                FIELD(fields, u8*, -0x1E) = (u8)(((FIELD(dims_clipped, u8*, 0) + (u8)FIELD(dims_clipped, s16*, 4)) - fade) - clip_height);
                FIELD(fields, u8*, -0x1D) = (u8)FIELD(dims_clipped, u8*, 2);
                FIELD(fields, s8*, -0x12) = (s8)((FIELD(dims_clipped, u8*, 0) + (u8)FIELD(dims_clipped, s16*, 4)) - fade);
                FIELD(fields, u8*, -0x11) = (u8)FIELD(dims_clipped, u8*, 2);
                FIELD(fields, u8*, -6) = (u8)(((FIELD(dims_clipped, u8*, 0) + (u8)FIELD(dims_clipped, s16*, 4)) - fade) - clip_height);
                FIELD(fields, s8*, -5) = (s8)(FIELD(dims_clipped, u8*, 2) + FIELD(dims_clipped, u8*, 6));
                FIELD(fields, s8*, 6) = (s8)((FIELD(dims_clipped, u8*, 0) + (u8)FIELD(dims_clipped, s16*, 4)) - fade);
                FIELD(fields, s8*, 7) = (s8)(FIELD(dims_clipped, u8*, 2) + FIELD(dims_clipped, u8*, 6));
                FIELD(fields, s16*, -0x22) = (s16)(((FIELD(dims_clipped, u16*, 8) + (u16)FIELD(dims_clipped, s16*, 4)) - fade) - clip_base);
                FIELD(fields, s16*, -0x20) = (s16)(FIELD(dims_clipped, u16*, 0xA) + 0x80);
                value = ((FIELD(dims_clipped, u16*, 8) + (u16)FIELD(dims_clipped, s16*, 4)) - fade) - clip_base;
                value += clip_height;
                FIELD(fields, s16*, -0x16) = (s16)value;
                FIELD(fields, s16*, -0x14) = (s16)(FIELD(dims_clipped, u16*, 0xA) + 0x80);
                FIELD(fields, s16*, -0xA) = (s16)(((FIELD(dims_clipped, u16*, 8) + (u16)FIELD(dims_clipped, s16*, 4)) - fade) - clip_base);
                FIELD(fields, s16*, -8) = (s16)(FIELD(dims_clipped, u16*, 0xA) + (FIELD(dims_clipped, u16*, 6) + 0x80));
                value = ((FIELD(dims_clipped, u16*, 8) + (u16)FIELD(dims_clipped, s16*, 4)) - fade) - clip_base;
                value += clip_height;
                FIELD(fields, s16*, 2) = (s16)value;
                y_offset = FIELD(dims_clipped, u16*, 6);
                y_bottom = FIELD(dims_clipped, u16*, 0xA);
                FIELD(fields, s8*, -0x26) = 0;
                FIELD(fields, s8*, -0x25) = 0;
                FIELD(fields, s8*, -0x24) = 0;
                FIELD(fields, s8*, -0x1A) = (s8)color;
                FIELD(fields, s8*, -0x19) = (s8)color;
                FIELD(fields, s8*, -0x18) = (s8)color;
                FIELD(fields, s8*, -0xE) = 0;
                FIELD(fields, s8*, -0xD) = 0;
                FIELD(fields, s8*, -0xC) = 0;
            finish_bottom_row:
                FIELD(fields, s8*, -2) = (s8)color;
                FIELD(fields, s8*, -1) = (s8)color;
                FIELD(fields, s8*, 0) = (s8)color;
                __asm__ volatile("" : : : "memory");
                y_offset += 0x80;
                y_bottom += y_offset;
                FIELD(fields, s16*, 4) = (s16)y_bottom;
            } else {
                FIELD(fields, u8*, -0x1E) = (u8)(FIELD(dims_clipped, u8*, 0) + fade);
                FIELD(fields, u8*, -0x1D) = (u8)FIELD(dims_clipped, u8*, 2);
                value = FIELD(dims_clipped, u8*, 0) + fade;
                value += clip_height;
                FIELD(fields, s8*, -0x12) = (s8)value;
                FIELD(fields, u8*, -0x11) = (u8)FIELD(dims_clipped, u8*, 2);
                FIELD(fields, u8*, -6) = (u8)(FIELD(dims_clipped, u8*, 0) + fade);
                FIELD(fields, s8*, -5) = (s8)(FIELD(dims_clipped, u8*, 2) + FIELD(dims_clipped, u8*, 6));
                value = FIELD(dims_clipped, u8*, 0) + fade;
                value += clip_height;
                FIELD(fields, s8*, 6) = (s8)value;
                FIELD(fields, s8*, 7) = (s8)(FIELD(dims_clipped, u8*, 2) + FIELD(dims_clipped, u8*, 6));
                FIELD(fields, s16*, -0x22) = (s16)(FIELD(dims_clipped, u16*, 8) + fade + 0x100);
                FIELD(fields, s16*, -0x20) = (s16)(FIELD(dims_clipped, u16*, 0xA) + 0x80);
                clip_end = clip_height + 0x100;
                value = FIELD(dims_clipped, u16*, 8) + fade;
                value += clip_end;
                FIELD(fields, s16*, -0x16) = (s16)value;
                FIELD(fields, s16*, -0x14) = (s16)(FIELD(dims_clipped, u16*, 0xA) + 0x80);
                FIELD(fields, s16*, -0xA) = (s16)(FIELD(dims_clipped, u16*, 8) + fade + 0x100);
                FIELD(fields, s16*, -8) = (s16)(FIELD(dims_clipped, u16*, 0xA) + (FIELD(dims_clipped, u16*, 6) + 0x80));
                value = FIELD(dims_clipped, u16*, 8) + fade;
                value += clip_end;
                FIELD(fields, s16*, 2) = (s16)value;
                FIELD(fields, s16*, 4) = (s16)(FIELD(dims_clipped, u16*, 0xA) + (FIELD(dims_clipped, u16*, 6) + 0x80));
                FIELD(fields, s8*, -0x26) = (s8)color;
                FIELD(fields, s8*, -0x25) = (s8)color;
                FIELD(fields, s8*, -0x24) = (s8)color;
                FIELD(fields, s8*, -0x1A) = 0;
                FIELD(fields, s8*, -0x19) = 0;
                FIELD(fields, s8*, -0x18) = 0;
                FIELD(fields, s8*, -0xE) = (s8)color;
                FIELD(fields, s8*, -0xD) = (s8)color;
                FIELD(fields, s8*, -0xC) = (s8)color;
                FIELD(fields, s8*, -2) = 0;
                FIELD(fields, s8*, -1) = 0;
                FIELD(fields, s8*, 0) = 0;
            }
        }
        fields += 0x34;
        poly += 0x34;
        column += 1;
        row_offset += 0xC;
        if (column < 2) {
            goto next_column;
        }
        row += 1;
    } while (row < 2);
    scratch = stack.layer;
    if (scratch != 0) {
        scratch = primitives;
        submit_primitive(scratch + 0x34);
        submit_primitive(primitives);
        scratch = primitives;
        submit_primitive(scratch + 0x9C);
        scratch = primitives;
        last_primitive = scratch + 0x68;
    } else {
        scratch = primitives;
        submit_primitive(scratch + 0x9C);
        scratch = primitives;
        submit_primitive(scratch + 0x68);
        scratch = primitives;
        submit_primitive(scratch + 0x34);
        last_primitive = primitives;
    }
    submit_primitive(last_primitive);
}
