#include "psx/types.h"

extern s32 g_battle_action_state;
extern s32 rand(void);

s32 battle_random_process_gives_a_number_between_0_7fff(void) {
    if (g_battle_action_state != 0) {
        return 0x4000;
    }
    return rand();
}
