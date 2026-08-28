#include "fft/battle.h"
#include "psx/types.h"

extern s32 get_script_variable(s32 variable_id);
extern void set_script_variable(s32 variable_id, s32 value);

/* Increment the battle casualty or injured counter for a unit, capped at 9999. */
void main_increase_casualties_injured_counters(battle_stats_t* unit) {
    s32 id;
    s32 n;

    id = (*(u8*)((u8*)unit + 0x1ba) & 0x30) != 0 ? 0x61 : 0x62;
    n = get_script_variable(id);
    if (n < 0x270f) {
        n++;
    }
    set_script_variable(id, n);
}
