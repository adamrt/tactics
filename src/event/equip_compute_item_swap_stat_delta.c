#include "psx/types.h"

typedef struct EquipPortraitInfo {
    /* 0x00 */ u8 unk_0[0xE];
    /* 0x0E */ s16 unk_E;
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x12];
} EquipPortraitInfo; /* size 0x28 */

typedef struct EquipPortraitPoly {
    /* 0x00 */ u8 unk_0[0x40];
} EquipPortraitPoly; /* size 0x40 */

extern void func_801C7B04(s16 index, EquipPortraitInfo* info, EquipPortraitPoly* poly, s32 arg3);
extern void equip_subtract_scaled_item_stats(s32 arg0, EquipPortraitPoly* a, EquipPortraitPoly* b, s32 arg3);

void equip_compute_item_swap_stat_delta(s32 arg0, EquipPortraitInfo* out, s16 from, s16 to, s32 arg4) {
    EquipPortraitInfo info_a;
    EquipPortraitInfo info_b;
    EquipPortraitPoly poly_a;
    EquipPortraitPoly poly_b;

    func_801C7B04(from, &info_a, &poly_a, arg4);
    func_801C7B04(to, &info_b, &poly_b, arg4);
    out->unk_E = info_b.unk_E - info_a.unk_E;
    out->unk_14 = info_b.unk_14 - info_a.unk_14;
    equip_subtract_scaled_item_stats(arg0, &poly_a, &poly_b, 1);
}
