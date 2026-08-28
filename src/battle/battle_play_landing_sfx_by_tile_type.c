#include "fft/battle.h"
#include "psx/types.h"

extern u8* battle_get_tile_data_pointer(s32 x, s32 y, s32 elevation);
extern void main_play_sound_find_channel(s32 sound_id);

void play_landing_sfx_based_on_tile(battle_display_unit_t* unit) {
    u8* tile;
    s32 t;
    s32 sfx;

    if (unit->movement.word & 0x02000000)
        return;
    tile = battle_get_tile_data_pointer(unit->movement.bytes.destination_x,
        unit->movement.bytes.destination_y,
        unit->movement.bytes.destination_z);
    if (tile == 0)
        return;
    t = *tile & 0x3F;
    switch (t) {
    case 0x3:
    case 0x4:
    case 0x1D:
        sfx = 0x28;
        break;
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x2D:
        sfx = 0x23;
        break;
    case 0x14:
    case 0x1E:
    case 0x1F:
        sfx = 0x3A;
        break;
    default:
        sfx = 0x29;
        break;
    }
    main_play_sound_find_channel(sfx);
}
