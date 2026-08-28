#include "psx/types.h"

extern void main_copy_action_data(const u8* src, u8* dst);
extern void battle_disable_green_panel_flags(void);
extern u8 g_map_max_x;
extern u8 g_map_max_y;
extern u8 g_battle_tile_data[];

s32 battle_disable_green_panel_on_all_but_target_s_tile(const u8* source) {
    u8 sp10[20];
    u8 x;
    u8 y;
    u8 level;
    u8* tile;

    main_copy_action_data(source, sp10);
    x = sp10[0xC];
    y = sp10[0x10];
    level = sp10[0xE];
    if (x < g_map_max_x) {
        if (y < g_map_max_y) {
            if (level < 2) {
                tile = &g_battle_tile_data[((level << 8) + y * g_map_max_x + x) * 8];
                if ((tile[6] & 1) == 0) {
                    battle_disable_green_panel_flags();
                    tile[5] |= 0x80;
                    return 1;
                }
            }
        }
    }
    return -1;
}
