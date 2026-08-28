#include "fft/battle.h"

extern battle_stats_t* get_battle_stats_pointer(s32 battle_unit_index);
extern void world_call_inner_subroutine_on_main_thread(s32 status_id,
    s32 enabled,
    s32 battle_unit_index);
extern void special_status_flag_enabling(void);
extern void (*g_world_inner_subroutine_callback)(void);

void world_apply_zalera_draw_status_flags(s32 battle_unit_index, s32 enabled) {
    battle_stats_t* unit;
    s32 status_index;
    s32 byte_index;
    s32 bit_index;

    unit = get_battle_stats_pointer(battle_unit_index);
    g_world_inner_subroutine_callback = special_status_flag_enabling;
    status_index = 0;
    do {
        byte_index = status_index / 8;
        bit_index = status_index - byte_index * 8;
        if ((unit->current_status[byte_index] & (0x80 >> bit_index)) != 0) {
            world_call_inner_subroutine_on_main_thread(status_index + 1, enabled,
                battle_unit_index);
        }
        status_index++;
    } while (status_index < 40);
}
