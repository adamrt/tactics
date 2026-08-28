#include "psx/types.h"

typedef struct EquipPortraitInfo {
    /* 0x00 */ u8 unk_0[0xE];
    /* 0x0E */ u16 unk_E;
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u8 unk_16[0x12];
} EquipPortraitInfo; /* size 0x28 */

typedef struct EquipPortraitPolyPair {
    /* 0x00 */ u8 unk_0[0x80];
} EquipPortraitPolyPair;

extern void equip_clear_item_stat_sums(EquipPortraitInfo* info, s32 arg1);
extern void equip_compute_item_swap_stat_delta(EquipPortraitPolyPair* dst, EquipPortraitInfo* out, s32 from, s32 to, s32 index);
extern void equip_subtract_scaled_item_stats(s32 arg0, s32 arg1, EquipPortraitPolyPair* src, s32 arg3);

void equip_compute_equipment_swap_stat_deltas(s32 arg0, EquipPortraitInfo* acc, u16* froms, u16* tos) {
    EquipPortraitInfo info;
    EquipPortraitPolyPair polys;
    s32 i;

    equip_clear_item_stat_sums(acc, arg0);

    for (i = 0; i < 5; i++) {
        equip_compute_item_swap_stat_delta(&polys, &info, froms[i] & 0x3FF, tos[i] & 0x3FF, i);
        equip_subtract_scaled_item_stats(arg0, arg0, &polys, -1);
        acc->unk_E += info.unk_E;
        acc->unk_14 += info.unk_14;
    }
}
