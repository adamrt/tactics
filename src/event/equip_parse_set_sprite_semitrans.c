#include "psx/types.h"

extern s16 g_equip_semitransparency;

const u8* equip_parse_set_sprite_semitrans(const u8* data) {
    g_equip_semitransparency = data[3];
    return data + data[1];
}
