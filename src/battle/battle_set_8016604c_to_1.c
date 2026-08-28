#include "psx/types.h"

extern s16 g_option_transition_finished;

void battle_set_8016604c_to_1(void) {
    g_option_transition_finished = 1;
}
