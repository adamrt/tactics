#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_current_ability_canceled_statuses[];

void battle_null_some_status_data(battle_action_data_t* action) {
    s32 i;
    for (i = 0; i < 5; i++) {
        g_current_ability_canceled_statuses[i] = 0;
        action->status_infliction[i] = 0;
        action->status_removal[i] = 0;
    }
}
