#include "psx/types.h"

typedef struct DebugChrDrawEntry {
    u16 field_00;
    u16 field_02;
    s16* value;
    s16 flags;
    u16 field_0a;
} DebugChrDrawEntry;

extern void debugchr_render_decimal_value(s32 value, s32 flags, s32 arg0,
    u8* output);

void debugchr_render_signed_decimal_entries(s32 arg0, DebugChrDrawEntry* entries,
    u8* output, s32 count) {
    s32 i;
    for (i = 0; i < count;) {
        s32 value = *entries->value;
        s32 flags;
        *(u16*)(output + 0) = entries->field_00;
        *(u16*)(output + 2) = entries->field_02;
        entries->flags &= 0xf3ff;
        if (value < 0) {
            *(u32*)(output + 0xc) = 0x88888888;
            value = -value;
            entries->flags |= 0x800;
        } else if (value > 0) {
            *(u32*)(output + 0xc) = 0xcccccccc;
            entries->flags |= 0x400;
        } else {
            *(u32*)(output + 0xc) = 0;
            entries->flags |= 0x800;
        }
        flags = entries->flags;
        entries++;
        i++;
        debugchr_render_decimal_value(value, flags, arg0, output);
        *(u32*)(output + 0xc) = 0;
    }
}
