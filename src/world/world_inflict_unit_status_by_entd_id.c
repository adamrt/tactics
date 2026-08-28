#include "fft/battle.h"

extern s32 world_get_battle_unit_index_by_entd_id(s32 entd_unit_id);
extern battle_stats_t* get_battle_stats_pointer(s32 battle_unit_index);
extern void world_call_inner_subroutine_on_main_thread(s32 battle_unit_index,
    s32 less_strict_removal);
extern void resolve_unit_status_changes(void);
extern void (*g_world_inner_subroutine_callback)(void);

void world_inflict_unit_status_by_entd_id(s32 entd_unit_id, s32 status_index,
    s32 is_infliction,
    s32 less_strict_removal) {
    s32 battle_unit_index;
    battle_stats_t* unit;
    s32 clear_index;
    s32 status_byte_index;
    s32 status_bit_index;
    u8 status_mask;

    battle_unit_index = world_get_battle_unit_index_by_entd_id(entd_unit_id);
    if (battle_unit_index != 2000) {
        unit = get_battle_stats_pointer(battle_unit_index);
        clear_index = 0;
        do {
            unit->action.status_infliction[clear_index] = 0;
            unit->action.status_removal[clear_index] = 0;
            clear_index++;
        } while (clear_index < 5);

        status_byte_index = status_index / 8;
        status_bit_index = status_index - status_byte_index * 8;
        status_mask = 1 << status_bit_index;
        if (is_infliction != 0) {
            unit->action.status_infliction[status_byte_index] = status_mask;
        } else {
            unit->action.status_removal[status_byte_index] = status_mask;
        }
        g_world_inner_subroutine_callback = resolve_unit_status_changes;
        world_call_inner_subroutine_on_main_thread(battle_unit_index,
            less_strict_removal);
    }
}
