#include "psx/types.h"

extern u16 g_card_input_newly_pressed;
extern u32 g_card_input_primary_repeat;
extern u32 g_card_input_secondary_repeat;

void card_clear_input_state(void) {
    g_card_input_newly_pressed = 0;
    g_card_input_secondary_repeat = 0;
    g_card_input_primary_repeat = 0;
}
