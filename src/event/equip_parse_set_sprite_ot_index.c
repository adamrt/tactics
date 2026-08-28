#include "psx/types.h"

extern s16 g_equip_sprite_ot_index;

const u8* equip_parse_set_sprite_ot_index(const u8* data) {
    g_equip_sprite_ot_index = data[3];
    return data + data[1];
}
