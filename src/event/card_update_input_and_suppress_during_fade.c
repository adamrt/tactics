#include "psx/types.h"

extern void card_update_controller_input(void);
extern s32 card_get_fade_state(void);
extern u16 g_card_input_newly_pressed;
extern u32 g_card_input_primary_repeat;
extern u32 g_card_input_secondary_repeat;

void card_update_input_and_suppress_during_fade(void) {
    card_update_controller_input();
    if (card_get_fade_state() != 0) {
        g_card_input_newly_pressed = 0;
        g_card_input_primary_repeat = 0;
        g_card_input_secondary_repeat = 0;
    }
}
