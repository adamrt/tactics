#include "fft/battle.h"
#include "psx/types.h"

extern void main_clear_byte_data(void* dst, s32 len);
extern void battle_null_some_status_data(void* arg0);

void battle_current_action_data_nulling(battle_action_data_t* action) {
    main_clear_byte_data(action, 0xE);
    main_clear_byte_data((u8*)&action->special_effect, 0x16);
    main_clear_byte_data(&action->exp_change, 2);
    /* The target stores the accuracy as a halfword (0x2a..0x2b). */
    action->attack_accuracy = 100;
    action->attack_type = 0;
    action->hit = 1;
    battle_null_some_status_data(action);
}
