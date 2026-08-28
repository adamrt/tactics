#include "psx/types.h"

typedef struct EquipItemData {
    /* 0x00 */ u8 unk_0[2];
    /* 0x02 */ u8 unk_2;
    /* 0x03 */ u8 unk_3;
    /* 0x04 */ u8 unk_4;
    /* 0x05 */ u8 unk_5[7];
} EquipItemData; /* size 0xC */

extern s32 equip_out_get_item_type_from_item_number(s16 item);

extern EquipItemData g_primary_item_data[];
extern u8 D_80063ABC[];
extern u8 D_80063EB8[];
extern u8 D_80063ED8[];

/* Look up the help/description index for an item, using a different table for
   each item category. */
s32 equip_get_item_ranking_value(s32 item) {
    s32 type;
    s32 idx;

    type = equip_out_get_item_type_from_item_number(item);
    if (item != 0 && type == 0) {
        return D_80063ABC[g_primary_item_data[item].unk_4 * 8];
    }
    if (type == 1) {
        return D_80063EB8[g_primary_item_data[item].unk_4 * 2];
    }
    if (type >= 4) {
        return g_primary_item_data[item].unk_2;
    }
    idx = item - 0x90;
    return D_80063ED8[idx * 2];
}
