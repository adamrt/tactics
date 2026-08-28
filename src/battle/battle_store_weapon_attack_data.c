#include "psx/types.h"

extern u8 g_item_data_table[];

void battle_store_weapon_attack_data(u8* out, s32 item_id, s32* flags_out) {
    u8* item;
    s32 flags;
    s32 type;

    if (item_id == 0xff) {
        return;
    }
    item = &g_item_data_table[item_id * 8];
    flags = item[1];
    if (flags & 0x10) {
        out[3] |= 0x80;
    } else if (flags & 0x20) {
        out[3] |= 0x40;
    }
    type = item[2];
    switch (type) {
    case 6:
        *flags_out |= 2;
        break;
    case 7:
        *flags_out |= 4;
        break;
    default:
        *flags_out |= 1;
        break;
    }
    out[4] = (u8)item_id;
    out[0] = item[0];
    out[5] |= item[6];
}
