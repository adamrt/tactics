#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_get_script_variable(s32 id);
extern s32 battle_get_battle_unit_index_by_misc_id(s32 misc_id);
extern battle_stats_t* battle_get_battle_stats_from_battle_id(s32 idx);
extern u8 func_8018401C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8014CEB4(s32 misc_id);
extern void battle_set_specific_animation_by_misc_id(s32 misc_id, u32 value);
extern void battle_set_idle_animation_by_misc_id(void);
extern void battle_set_mounted_animation_by_misc_id(void);
extern void* g_call_inner_subroutine_target;

void battle_set_specific_unit_animation_value_when_battle_init(s32 misc_id, u32 value) {
    s32 idx;
    battle_stats_t* stats;
    s32 r;

    if ((battle_get_script_variable(0x1FD) == 0) && (battle_get_script_variable(0x6F) != 0)) {
        idx = battle_get_battle_unit_index_by_misc_id(misc_id);
        if ((idx >= 0) && (value < 0x1F4)) {
            stats = battle_get_battle_stats_from_battle_id(idx);
            r = func_8018401C(4, stats->x, stats->position.bits.y,
                stats->position.raw >> 15);
            if ((stats->mount_info & 0xC0) != 0) {
                g_call_inner_subroutine_target = battle_set_idle_animation_by_misc_id;
            } else {
                if ((r & 0xFF) < 2) {
                    goto plain;
                }
                g_call_inner_subroutine_target = battle_set_mounted_animation_by_misc_id;
            }
            func_8014CEB4(misc_id);
            return;
        }
    }
plain:
    battle_set_specific_animation_by_misc_id(misc_id, value);
}
