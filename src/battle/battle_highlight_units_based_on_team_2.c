#include "psx/types.h"

extern void* battle_get_unit_misc_data_by_misc_id(u16 id);
extern void battle_palette_modification_based_on_team(void* unit, s32 mode);

void battle_highlight_units_based_on_team_2(void) {
    s32 i = 0;
    do {
        battle_palette_modification_based_on_team(battle_get_unit_misc_data_by_misc_id((u16)i), 4);
        i++;
    } while (i < 0x10);
}
