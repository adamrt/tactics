#include "fft/battle.h"
#include "psx/types.h"

extern u8 D_80066254[];
extern u8 D_8006628E;

extern void battle_current_action_data_nulling(battle_action_data_t* action);
extern s32 battle_item_quantity_increment_for_steal_break(battle_stats_t* unit, s32 arg1);

s32 battle_learn_from_crystal(battle_stats_t* unit, s32 flags) {
    s32 i;
    u8* dst;
    u8* src;
    u8* p;
    u8* q;
    u8* end;

    battle_current_action_data_nulling(&unit->action);
    unit->action.miss_type = 8;
    unit->action.hit = 0;
    if (flags & 4) {
        return battle_item_quantity_increment_for_steal_break(unit, D_8006628E);
    }
    if (flags & 2) {
        unit->action.hit = 1;
        unit->action.attack_type = 0x50;
        unit->action.miss_type = 0;
        unit->action.hp_healing = unit->max_hp - unit->hp;
        unit->action.mp_healing = unit->max_mp - unit->mp;
    }
    if (flags & 1) {
        /* OR the crystal's ability bits into learned_abilities, three bytes
         * per job for 19 jobs; walked as raw bytes to keep the biased pointers. */
        i = 0;
        src = D_80066254;
        dst = (u8*)unit;
        do {
            p = dst + 0x99;
            q = src;
            end = dst + 0x9C;
            do {
                *p |= *q;
                p++;
                q++;
            } while ((s32)p < (s32)end);
            src += 3;
            i++;
            dst += 3;
        } while (i < 0x13);
    }
    return 0;
}
