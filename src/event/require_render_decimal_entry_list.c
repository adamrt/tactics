#include "psx/types.h"

typedef struct RequireDrawEntry2 {
    u16 field_00;
    u16 field_02;
    s16* value;
    s16 flags;
} RequireDrawEntry2;

extern void require_render_decimal_value(s32 value, s32 flags, s32 arg0, u8* output);

void require_render_decimal_entry_list(s32 arg0, RequireDrawEntry2* entries,
    u8* output, s32 count) {
    s32 i;

    for (i = 0; i < count;
        entries++, i++, *(u32*)(output + 0xc) = 0) {
        s32 value = *entries->value;
        register s32 flags __asm__("$5");
        *(u16*)(output + 0) = entries->field_00;
        *(u16*)(output + 2) = entries->field_02;
        flags = entries->flags;
        flags &= 0xf3ff;
        if (value < 0) {
            value = -value;
            flags |= 0x800;
            *(u32*)(output + 0xc) = 0x77777777;
        } else if (value > 0) {
            flags |= 0x400;
            *(u32*)(output + 0xc) = 0xbbbbbbbb;
        } else {
            *(u32*)(output + 0xc) = 0;
            flags = (flags & 0xfff0) | 0x804;
        }
        require_render_decimal_value(value, flags, arg0, output);
    }
}
