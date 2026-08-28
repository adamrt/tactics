#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u16 id);
extern void process_single_unit_movement(battle_misc_data_t* unit);

void battle_process_unit_movement(void) {
    s32 i;
    battle_misc_data_t* unit;

    i = 0;
    do {
        unit = battle_get_unit_misc_data_by_misc_id((u16)i);
        if (unit != 0) {
            if (unit->movement_path_count != 0) {
                process_single_unit_movement(unit);
            }
        }
        i++;
    } while (i < 0x10);
}
