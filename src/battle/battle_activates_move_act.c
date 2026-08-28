#include "psx/types.h"

void battle_activates_move_act(void* unit_misc) {
    ((s8*)unit_misc)[0x187] = 0;
    ((s8*)unit_misc)[0x188] = 0;
}
