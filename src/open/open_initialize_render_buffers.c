#include "fft/opening.h"

extern s32 g_open_primitive_count;
extern s32 g_open_render_record_pointer_count;

void open_initialize_render_buffers(void) {
    /* One pin: without it GCC swaps $a1/$a2 between the counter and the
     * color value (declaration order and per-loop locals do not move it). */
    register s32 intensity __asm__("$6");
    s32 i;
    s32 type_flag;
    s32 field_value;
    /* volatile keeps GCC from splitting the byte walk into two biased
     * induction pointers; the words are stored by index. */
    volatile u8* color;

    g_open_primitive_count = 0;
    g_open_next_render_record_56 = 0;
    g_open_next_render_record_36 = 0;
    g_open_render_record_pointer_count = 0;

    i = 0;
    type_flag = 1;
    field_value = 8;
    intensity = 0x80;
    color = &g_open_render_records_36[0].r;
    while (i < 16) {
        g_open_render_records_36[i].flags = type_flag;
        g_open_render_records_36[i].field_08 = field_value;
        color[0] = intensity;
        color[1] = intensity;
        color[2] = intensity;
        color += sizeof(open_render_record_36_t);
        i++;
    }

    i = 0;
    type_flag = 2;
    field_value = 8;
    intensity = 0x80;
    color = &g_open_render_records_56[0].tail.r;
    while (i < 16) {
        g_open_render_records_56[i].flags = type_flag;
        g_open_render_records_56[i].field_0c = field_value;
        color[0] = intensity;
        color[1] = intensity;
        color[2] = intensity;
        color += sizeof(open_render_record_56_t);
        i++;
    }
}
