#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_target_current_action;
extern s16 g_current_ability_xa;
extern u8 g_current_ability_element;

extern void battle_nullify_action(s32 arg0);
extern s32 func_80184B24(s32 arg0);
extern void battle_elemental_damage_modification_2(s32 element);

void battle_apply_elemental(void) {
    u8 element;
    battle_action_data_t* action;
    battle_stats_t* unit;
    s32 mount_info;

    element = g_current_ability_element;
    /* Oil (status 3 bit 0x80) doubles fire (element bit 0x80) and is removed. */
    if ((g_target_unit_data->current_status[2] & 0x80) && (element & BATTLE_ELEMENT_FIRE)) {
        action = g_target_current_action;
        g_current_ability_xa = g_current_ability_xa * 2;
        action->status_removal[2] |= 0x80;
        if (func_80184B24(0) != 0) {
            g_target_current_action->attack_type = 8;
        }
    }
    unit = g_target_unit_data;
    mount_info = unit->mount_info;
    if (mount_info & 0x80) {
        unit = &battle_stats[mount_info & 0x1F];
    }
    /* Float (status 3 bit 0x40) nullifies earth (element bit 0x08). */
    if ((unit->current_status[2] & 0x40) && (element & BATTLE_ELEMENT_EARTH)) {
        battle_nullify_action(mount_info);
        g_target_current_action->miss_type = 7;
    }
    battle_elemental_damage_modification_2(element);
}
