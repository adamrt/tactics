#include "psx/types.h"

extern s32 get_facing_input(s32 player_id);
extern s32 g_battle_game_flow_running;
extern s32 D_800E4E74;
extern s32 D_800E4E7C;
extern u8 g_map_max_x;
extern u8 g_map_max_y;

void battle_process_map_camera_pan(void) {
    s32* coord;
    s32 limit;

    if (g_battle_game_flow_running != 0) {
        switch (get_facing_input(0)) {
        case 0x800:
            coord = &D_800E4E7C;
            *coord += 0x4000;
            break;
        case 0:
            coord = &D_800E4E7C;
            *coord -= 0x4000;
            break;
        case 0x400:
            coord = &D_800E4E74;
            *coord -= 0x4000;
            break;
        case 0xC00:
            coord = &D_800E4E74;
            *coord += 0x4000;
            break;
        case 0xA00: {
            s32* y = &D_800E4E7C;
            *y += 0x4000;
            D_800E4E74 += 0x4000;
            break;
        }
        case 0x600: {
            s32* y = &D_800E4E7C;
            *y += 0x4000;
            D_800E4E74 -= 0x4000;
            break;
        }
        case 0xE00: {
            s32* y = &D_800E4E7C;
            *y -= 0x4000;
            D_800E4E74 += 0x4000;
            break;
        }
        case 0x200: {
            s32* y = &D_800E4E7C;
            *y -= 0x4000;
            D_800E4E74 -= 0x4000;
            break;
        }
        }
        {
            s32* x = &D_800E4E74;
            limit = (g_map_max_x * 0x1C000) + 0x70000;
            if (limit < *x)
                *x = limit;
            if (*x < -0x70000)
                *x = -0x70000;
        }
        limit = (g_map_max_y * 0x1C000) + 0x70000;
        if (limit < D_800E4E7C)
            D_800E4E7C = limit;
        if (D_800E4E7C < -0x70000)
            D_800E4E7C = -0x70000;
    }
}
