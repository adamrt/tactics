#include "psx/types.h"

extern void battle_update_and_animate_units(void);

void battle_update_and_animate_units_three_times(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        battle_update_and_animate_units();
    }
}
