#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;
extern void func_80195878(battle_ai_ability_entry_t*);
extern s32 func_8019AF18(void);

s32 battle_chose_move_from_move_list(void) {
    battle_ai_data_t* ai;
    battle_ai_ability_entry_t* entry;

    ai = &g_ai_data_base;
    if (g_ai_data_base.decision_state != 0) {
        goto retry;
    }
    g_ai_data_base.ability_counter = 0;
    while (1) {
        entry = &ai->ability_lists[ai->acting_unit_battle_id][ai->ability_counter];
        if (entry->skillset == 0xFF) {
            return 0;
        }
        func_80195878(entry);
    retry:
        if (func_8019AF18() == -1) {
            return -1;
        }
        ai->ability_counter += 1;
        if (ai->ability_counter >= 0x22) {
            return 0;
        }
    }
}
