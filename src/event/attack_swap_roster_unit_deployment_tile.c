#include "psx/types.h"

extern u8 g_attack_deployed_roster_id_by_tile[5][5];

void attack_swap_roster_unit_deployment_tile(s32 column, s32 row,
    s32 roster_id) {
    s32 current_row;
    u8* selected_base;
    u8* selected;
    /* Pin keeps the row base in $v1 so the two inner pointers land in the
     * dead argument registers $a0/$a3; without it GCC rotates all four. */
    register u8* row_entries __asm__("$3");
    u8* entry;
    u8* end;
    s32 old_value;

    current_row = 0;
    row_entries = g_attack_deployed_roster_id_by_tile[0];
    selected_base = g_attack_deployed_roster_id_by_tile[row];
    selected = selected_base + column;
    do {
        entry = row_entries;
        end = row_entries + 5;
        do {
            old_value = *entry;
            if (old_value == roster_id) {
                *entry = *selected;
                *selected = old_value;
                return;
            }
            entry++;
        } while ((s32)entry < (s32)end);
        current_row++;
        row_entries += 5;
    } while (current_row < 5);
}
