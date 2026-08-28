#include "fft/battle.h"

extern void battle_request_map_rotation(s32 angle);
extern void* battle_get_tile_data_pointer(u8 x, u8 y, u8 z);
extern s16 g_battle_camera_render_state;
extern s16 g_battle_camera_yaw;

void battle_rotate_camera_when_unit_tile_not_visible(battle_misc_data_t* unit) {
    s32 direction;
    u8 flags;
    void* tile;

    tile = battle_get_tile_data_pointer(unit->map_x, unit->map_y, unit->map_z);
    direction = (0 - g_battle_camera_yaw) & 0xFFF;
    if (direction < 0) {
        direction += 0x3FF;
    }
    direction >>= 0xA;
    if (g_battle_camera_render_state >= 0x178) {
        flags = ((u8*)tile)[7] >> 4;
    } else {
        flags = ((u8*)tile)[7] & 0xF;
    }
    switch (direction) {
    case 0:
        if (flags & 1) {
            if (!(flags & 8)) {
                battle_request_map_rotation(0x400);
            } else {
                if (!(flags & 2)) {
                    battle_request_map_rotation(-0x400);
                } else if (!(flags & 4)) {
                    battle_request_map_rotation(0x800);
                }
            }
        }
        break;
    case 1:
        if (flags & 2) {
            if (!(flags & 1)) {
                battle_request_map_rotation(0x400);
            } else {
                if (!(flags & 4)) {
                    battle_request_map_rotation(-0x400);
                } else if (!(flags & 8)) {
                    battle_request_map_rotation(0x800);
                }
            }
        }
        break;
    case 2:
        if (flags & 4) {
            if (!(flags & 2)) {
                battle_request_map_rotation(0x400);
            } else {
                if (!(flags & 8)) {
                    battle_request_map_rotation(-0x400);
                } else if (!(flags & 1)) {
                    battle_request_map_rotation(0x800);
                }
            }
        }
        break;
    case 3:
        if (flags & 8) {
            if (!(flags & 4)) {
                battle_request_map_rotation(0x400);
            } else {
                if (!(flags & 1)) {
                    battle_request_map_rotation(-0x400);
                } else if (!(flags & 2)) {
                    battle_request_map_rotation(0x800);
                }
            }
        }
        break;
    }
}
