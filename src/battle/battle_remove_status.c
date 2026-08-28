#include "psx/types.h"

extern u8 D_80193906;
extern u8 D_80193907[];
extern u8 g_current_ability_canceled_statuses[];

void battle_remove_status(void) {
    s32 i;
    if (D_80193906 & 0x10) {
        i = 0;
        do {
            g_current_ability_canceled_statuses[i] = D_80193907[i];
            i++;
        } while (i < 5);
    }
}
