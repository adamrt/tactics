#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;
extern void battle_initialize_some_ai_data(battle_ai_action_data_t* action);

void battle_func_8019ae30(void) {
    battle_initialize_some_ai_data(&g_ai_data_base.selected_action);
}
