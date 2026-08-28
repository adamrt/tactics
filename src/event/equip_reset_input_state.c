#include "psx/types.h"

extern u16 g_equip_input_newly_pressed;
extern u32 g_equip_input_primary_repeat;
extern u32 g_equip_input_secondary_repeat;

void equip_reset_input_state(void) {
    g_equip_input_newly_pressed = 0;
    g_equip_input_secondary_repeat = 0;
    g_equip_input_primary_repeat = 0;
}
