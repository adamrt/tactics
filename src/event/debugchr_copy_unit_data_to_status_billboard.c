#include "fft/battle.h"
#include "psx/types.h"

extern s32 (*g_call_inner_subroutine_target)();
extern s16 call_inner_subroutine(void* unit);
extern s32 battle_does_misc_unit_id_exist(s32 id);
extern s32 get_unit_id_from_misc_id(s32 id);
extern battle_stats_t* get_battle_stats_pointer(s32 id);
extern battle_stats_t* find_battle_stats_by_entd_id(u8 id, s32* resolved_id);
extern s32 find_unit_at_list_index(void* unit);

void debugchr_copy_unit_data_to_status_billboard(battle_stats_t* unit, u8* output) {
    battle_stats_t* linked_unit;
    s32 resolved_id;
    s32 count;
    s32 i;
    s32 unit_id;
    register s32 hundred __asm__("$17");
    battle_stats_t* call_unit;
    u16 value;
    u8 ct;
    s32 (*ct_subroutine)(void*);

    linked_unit = unit;
    *(s16*)(output + 0) = linked_unit->level;
    *(s16*)(output + 2) = 0;
    if (linked_unit->initial_team_flags & 0x30)
        *(s16*)(output + 2) = 1;
    if (!(linked_unit->initial_team_flags & 0x38))
        *(s16*)(output + 2) = 2;
    if (linked_unit->auto_battle_setting != 0)
        *(s16*)(output + 2) = 3;
    *(s16*)(output + 8) = linked_unit->experience;
    value = linked_unit->max_hp;
    *(u16*)(output + 0x10) = value;
    if (value == 0)
        *(u16*)(output + 0x10) = value + 1;
    *(u16*)(output + 0xc) = linked_unit->hp;
    *(s16*)(output + 0xe) = 0;
    value = linked_unit->max_mp;
    *(u16*)(output + 0x16) = value;
    if (value == 0)
        *(u16*)(output + 0x16) = value + 1;
    hundred = 100;
    value = linked_unit->mp;
    /* A plain `call_unit = linked_unit` coalesces with linked_unit and swaps
     * the v0/v1 temporaries below (ct byte vs. subroutine address); the
     * explicit move keeps the retail register choice. */
    __asm__("move %0,%1" : "=r"(call_unit) : "r"(linked_unit));
    *(s16*)(output + 0x14) = 0;
    *(s16*)(output + 0x1c) = hundred;
    *(u16*)(output + 0x12) = value;
    ct = linked_unit->ct;
    ct_subroutine = find_unit_at_list_index;
    *(s16*)(output + 4) = 0;
    *(s16*)(output + 6) = 0;
    g_call_inner_subroutine_target = ct_subroutine;
    *(s16*)(output + 0x18) = ct;
    *(s16*)(output + 4) = call_inner_subroutine(call_unit);
    if (linked_unit->has_turn != 0)
        *(s16*)(output + 0x18) = hundred;
    if (*(s16*)(output + 4) >= 0)
        (*(s16*)(output + 4))++;
    *(s16*)(output + 6) = 0x15;
    count = 0;
    for (i = 0; i < 0x15; i++) {
        if (battle_does_misc_unit_id_exist(i) != 0) {
            unit_id = get_unit_id_from_misc_id(i);
            linked_unit = find_battle_stats_by_entd_id(
                get_battle_stats_pointer(unit_id)->unit_id, &resolved_id);
            if (resolved_id >= 0 && unit_id == resolved_id && linked_unit->unit_id != 0) {
                count++;
            }
        }
    }
    *(s16*)(output + 6) = count;
}
