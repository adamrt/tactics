#include "psx/types.h"

typedef struct {
    u8 pad_0[6];
    u16 f6;
    u16 f8;
    u16 fA;
    u16 fC;
    u8 pad_E[8];
    u16 f16;
    u16 f18;
    u8 pad_1A[6];
    u16 f20;
    u16 f22;
    u8 pad_24[0x5C];
} EquipStats;

extern void func_801C7B04(int, void*, EquipStats*, int);

void equip_sum_equipment_stat_bonuses(EquipStats* dst, u16* src) {
    u8 scratch[0x28];
    EquipStats tmp;
    int i;
    u16* p;

    dst->f6 = 0;
    dst->f8 = 0;
    dst->fC = 0;
    dst->fA = 0;
    dst->f16 = 0;
    dst->f18 = 0;
    dst->f20 = 0;
    dst->f22 = 0;

    for (i = 0, p = src; i < 5; i++) {
        func_801C7B04(*p & 0x3FF, scratch, &tmp, i);
        dst->f6 += tmp.f6;
        dst->f8 += tmp.f8;
        dst->fA += tmp.fA;
        dst->fC += tmp.fC;
        dst->f16 += tmp.f16;
        dst->f18 += tmp.f18;
        dst->f20 += tmp.f20;
        dst->f22 += tmp.f22;
        p++;
    }
}
