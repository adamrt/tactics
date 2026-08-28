#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_target_current_action;
extern u8 g_current_ability_target_id;
extern u8 g_current_action_data[];

extern void main_copy_byte_data(u8* dst, u8* src, s32 len);
extern s32 func_8018BE08(s32 unit_id);

s32 battle_store_target_stats_pointer_data(s32 unit_id) {
    battle_stats_t* stats;
    battle_action_data_t* action;
    s32 result;

    stats = &battle_stats[unit_id];
    g_target_unit_data = stats;
    if (unit_id >= 0x15) {
        return -1;
    }
    action = &battle_stats[unit_id].action;
    g_current_ability_target_id = unit_id;
    g_target_current_action = action;
    if (stats->entd_slot == 0xFF) {
        return -1;
    }
    main_copy_byte_data(g_current_action_data, (u8*)action, 0x2C);
    result = func_8018BE08(unit_id);
    if (g_target_current_action->hit == 0) {
        g_target_current_action->miss_type = 8;
    }
    return result;
}
