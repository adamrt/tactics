#include "psx/types.h"

extern s16 g_card_state_801c9572;
extern s16 g_card_state_801c9574;
extern s16 g_card_state_801c9578;

void card_update_save_slot_scroll(s32 selection) {
    if (g_card_state_801c9572 == 0) {
        if (selection < g_card_state_801c9578) {
            g_card_state_801c9572 = 4;
            g_card_state_801c9578--;
        }
        if (selection >= g_card_state_801c9578 + 4) {
            g_card_state_801c9572 = -4;
            g_card_state_801c9578++;
        }
    } else if (g_card_state_801c9572 < 0) {
        g_card_state_801c9572 -= 4;
        if (g_card_state_801c9572 < -47) {
            g_card_state_801c9572 = 0;
            g_card_state_801c9574 -= 48;
        }
    } else if (g_card_state_801c9572 > 0) {
        g_card_state_801c9572 += 4;
        if (g_card_state_801c9572 >= 48) {
            g_card_state_801c9572 = 0;
            g_card_state_801c9574 += 48;
        }
    }
}
