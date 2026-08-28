#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_casting_misc_id;

void battle_update_status_bubble_graphic_trigger(battle_misc_data_t* unit) {
    if ((unit->status_flags_1_4 & 0x1fffc2c4) != 0 || unit->unit_id == g_battle_casting_misc_id) {
        unit->status_bubble_active = 1;
        unit->status_bubble_timer = 0;
    } else {
        unit->status_bubble_active = 0;
    }
}
