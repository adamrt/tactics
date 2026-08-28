#include "psx/types.h"

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 pad02[4];
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 pad07[0x51];
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
} BunitUnitStats;

extern s16 D_801EB280[];
extern s16 D_801EB2AC;
extern u8 D_801EB2B0[];

extern BunitUnitStats* func_80180AFC(s32);
extern void bunit_copy_unit_data_to_status_billboard(BunitUnitStats*, u8*, s32);
extern void func_801C6F48(s32);

s32 bunit_out_unit_list_display(s32 arg0, s32 arg1, s32 arg2) {
    BunitUnitStats* u;
    s32 i;
    s32 shown;
    s32 total;
    s32 off;
    s32 off2;
    s32 unused[2]; /* unreferenced local retained by the original frame layout */
    s16* dst;

    shown = 0;
    total = 0;
    i = 0;
    dst = D_801EB280;
    off = 0;
    do {
        u = func_80180AFC(i);
        if ((u != 0) && (u->unk01 != 0xFF)) {
            if (u->unk06 & 4) {
                total++;
            } else if (!(u->unk58 & 0x40) && !(u->unk59 & 1)) {
                total++;
                bunit_copy_unit_data_to_status_billboard(u, D_801EB2B0 + off, shown);
                *dst = shown;
                dst++;
                off += 0x10C;
                shown++;
            }
        }
        i++;
    } while (i < 0x15);

    i = 0;
    if (shown > 0) {
        off2 = 0;
        do {
            *(s16*)(D_801EB2B0 + off2 + 6) = total;
            i++;
            off2 += 0x10C;
        } while (i < shown);
    }
    D_801EB2AC = shown;
    func_801C6F48(arg2);
    return shown;
}
