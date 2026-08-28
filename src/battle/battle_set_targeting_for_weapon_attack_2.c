#include "fft/battle.h"
#include "psx/types.h"

extern void main_copy_action_data(const u8* src, u8* dst);
extern void battle_clear_targeting_panel_data(void);
extern void func_80179A20(battle_stats_t* unit);
extern void battle_set_all_panels_targeted_if_targetable(u8* entry);
extern battle_stats_t battle_stats[];
extern u8 g_map_max_x;
extern u8 targeting_panel_data[];

void battle_set_targeting_for_weapon_attack_2(const u8* source) {
    u8 action[20];
    battle_stats_t* unit;
    s32 idx;
    s32 off;

    main_copy_action_data(source, action);
    unit = &battle_stats[action[0]];
    idx = unit->position.bits.y * g_map_max_x + unit->x;
    battle_clear_targeting_panel_data();
    func_80179A20(unit);
    {
        u8* p1;
        u8* p2;
        off = idx * 5;
        p1 = &targeting_panel_data[off];
        p2 = &targeting_panel_data[off + 0x500];
        *p1 = 0;
        *p2 = 0;
        battle_set_all_panels_targeted_if_targetable(p1);
    }
}
