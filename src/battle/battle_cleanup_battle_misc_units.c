#include "psx/types.h"

extern u8* g_misc_unit_list_head;
extern void battle_remove_misc_unit(u8* unit);

void battle_cleanup_battle_misc_units(void) {
    u8* unit;

    unit = g_misc_unit_list_head;
    while (unit != 0) {
        battle_remove_misc_unit(unit);
        unit = *(u8**)unit;
    }
}
