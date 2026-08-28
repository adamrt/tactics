#include "fft/battle.h"

/* elemental_affinity[] indices. */
enum {
    ELEMENTAL_AFFINITY_ABSORB = 0,
    ELEMENTAL_AFFINITY_CANCEL = 1,
    ELEMENTAL_AFFINITY_HALF = 2,
    ELEMENTAL_AFFINITY_WEAK = 3,
};

extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_target_current_action;

extern void battle_nullify_action(s32);

void battle_elemental_damage_modification_2(s32 element) {
    /* Pin: the `move a1,a0` that fills the first load-delay slot only appears
     * with the element mask in $a1 (see cookbook). */
    register s32 element_mask __asm__("$5");
    battle_stats_t* unit;
    battle_action_data_t* absorb_action;
    battle_action_data_t* half_action;
    battle_action_data_t* weak_action;

    element_mask = element;

    if (g_target_unit_data->elemental_affinity[ELEMENTAL_AFFINITY_ABSORB] & element_mask) {
        absorb_action = g_target_current_action;
        /* special_effect/special_flags_2 are handled as one halfword. */
        absorb_action->special_effect |= 0x400;
    }
    unit = g_target_unit_data;
    if (unit->elemental_affinity[ELEMENTAL_AFFINITY_CANCEL] & element_mask) {
        battle_nullify_action(element);
        return;
    }
    if (unit->elemental_affinity[ELEMENTAL_AFFINITY_HALF] & element_mask) {
        half_action = g_target_current_action;
        /* hp_damage is read signed (lh) for the division. */
        *(s16*)&half_action->hp_damage = *(s16*)&half_action->hp_damage / 2;
    }
    if (g_target_unit_data->elemental_affinity[ELEMENTAL_AFFINITY_WEAK] & element_mask) {
        weak_action = g_target_current_action;
        weak_action->special_effect |= 0x800;
        *(s16*)&weak_action->hp_damage = *(s16*)&weak_action->hp_damage * 2;
    }
}
