#include "psx/types.h"

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ s16* unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ u16 unk0A;
} BunitBarEntry;

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u8 pad04[8];
    /* 0x0C */ s32 unk0C;
} BunitBarOut;

extern void func_801C18A4(s32, s32, s32, BunitBarOut*);

void bunit_render_signed_decimal_entries(s32 arg0, BunitBarEntry* e, BunitBarOut* out, s32 count) {
    s32 i;
    s32 v;

    for (i = 0; i < count; e++, i++) {
        v = *e->unk04;
        out->unk00 = e->unk00;
        out->unk02 = e->unk02;
        e->unk08 &= 0xF3FF;
        if (v < 0) {
            out->unk0C = 0x88888888;
            v = -v;
            e->unk08 |= 0x800;
        } else if (v > 0) {
            out->unk0C = 0xCCCCCCCC;
            e->unk08 |= 0x400;
        } else {
            out->unk0C = 0;
            e->unk08 |= 0x800;
        }
        func_801C18A4(v, e->unk08, arg0, out);
        out->unk0C = 0;
    }
}
