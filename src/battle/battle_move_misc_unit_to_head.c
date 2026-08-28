#include "fft/battle.h"

extern battle_misc_data_t g_misc_unit_list_head;
extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);

s32 battle_move_misc_unit_to_head(u32 misc_id) {
    battle_misc_data_t* unit;
    battle_misc_data_t* previous;
    battle_misc_data_t* iterator;
    /* Pin: unpinned, GCC swaps `iterator` and `head` between $v1 and $a0
     * (declaration order and folding the head accesses into the global were
     * both tried; the direct global form also CSEs the address, 132 bytes). */
    register battle_misc_data_t* head __asm__("$4");

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    if (unit != 0) {
        iterator = &g_misc_unit_list_head;
        while (iterator != 0) {
            previous = (battle_misc_data_t*)iterator->previous;
            if (previous == unit) {
                goto found;
            }
            iterator = previous;
        }
        return 0;
    found:
        previous = (battle_misc_data_t*)unit->previous;
        head = &g_misc_unit_list_head;
        iterator->previous = (u32)previous;
        iterator = (battle_misc_data_t*)head->previous;
        unit->previous = (u32)iterator;
        head->previous = (u32)unit;
        return 1;
    }
    return 0;
}
