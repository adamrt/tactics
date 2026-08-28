#include "psx/types.h"

extern u8 g_attack_deployed_roster_id_by_tile[5][5];

s32 attack_deployment_tiles_contain_roster_id(s32 roster_id) {
    s32 row;
    s32 result;
    u8* row_entries;
    u8* entry;
    /* Pin: target has `row` in $a3 and `end` in $a2; unpinned GCC swaps them.
     * Declaration order, statement order and a nested do/while (which fixed
     * the `remove` sibling) all leave the swap in place here. */
    register u8* end asm("$6");

    row = 0;
    row_entries = g_attack_deployed_roster_id_by_tile[0];
next_row:
    entry = row_entries;
    end = row_entries + 5;
next_entry:
    if (*entry == roster_id) {
        result = 1;
    } else {
        entry++;
        if ((s32)entry >= (s32)end) {
            row++;
            row_entries += 5;
            if (row >= 5) {
                result = 0;
            } else {
                goto next_row;
            }
        } else {
            goto next_entry;
        }
    }
    return result;
}
