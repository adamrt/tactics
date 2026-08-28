#include "psx/types.h"

extern u8* g_misc_unit_list_head;
extern void func_80085c0c(u8* unit);
extern void battle_status_bubble_prep(u8* unit);
extern void func_800870ac(u8* unit);

void battle_update_and_animate_units(void) {
    u8* unit;

    unit = g_misc_unit_list_head;
    while (unit != 0) {
        func_80085c0c(unit);
        battle_status_bubble_prep(unit);
        func_800870ac(unit);
        unit = *(u8**)unit;
    }
}
