#include "psx/types.h"

extern s32 g_battle_action_state;
extern void special_status_flag_enabling(void);

void battle_enable_special_status_flags(void) {
    if (g_battle_action_state == 0) {
        special_status_flag_enabling();
    }
}
