#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_called_by_nullify_action(void);
extern void battle_remove_knockback_flag(void);

void battle_nullify_action(void) {
    battle_action_data_t* p;
    battle_action_data_t* q;

    g_target_current_action->hit = 0;
    p = g_target_current_action;
    p->miss_type = 5;
    q = g_target_current_action;
    *(s16*)&p->hp_damage = 0;
    /* Halfword stores clear the byte pairs at 0x2a and 0x10. */
    p->attack_accuracy = 0;
    p->special_effect = 0;
    q->attack_type = 0;
    battle_called_by_nullify_action();
    battle_remove_knockback_flag();
}
