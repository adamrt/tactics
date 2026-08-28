#include "psx/types.h"

extern void* g_battle_map_id;
extern s32 load_map_data(void*, s32);

s32 battle_load_map_data_stage_0x76(void) {
    return load_map_data(g_battle_map_id, 0x76);
}
