#include "psx/types.h"

extern s32 world_get_item_type_from_item_number(s16 item);
extern u8 g_primary_item_data[];
extern u8 D_80063ABC[];
extern u8 D_80063EB8[];
extern u8 D_80063ED8[];

u8 world_get_item_ranking_value(s32 item) {
    s32 type;
    s32 idx;

    type = world_get_item_type_from_item_number(item);
    if ((item != 0) && (type == 0)) {
        return D_80063ABC[g_primary_item_data[(item * 12) + 4] * 8];
    }
    if (type == 1) {
        return D_80063EB8[g_primary_item_data[(item * 12) + 4] * 2];
    }
    if (type >= 4) {
        return g_primary_item_data[(item * 12) + 2];
    }
    idx = item - 0x90;
    return D_80063ED8[idx * 2];
}
