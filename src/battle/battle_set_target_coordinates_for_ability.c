#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_current_ability[];
extern battle_stats_t battle_stats[];

void battle_set_target_coordinates_for_ability(battle_stats_t* acting, u8* out) {
    battle_stats_t* target;

    out[0x12] = 0;
    if (g_current_ability[0x4F] != 0) {
        out[0x1C] = g_current_ability[0xA];
        out[0x1D] = g_current_ability[0xB];
        out[0x1E] = g_current_ability[0xC];
    } else if (acting->action_reaction_id == 6) {
        target = &battle_stats[acting->action_target_id];
        out[0x1C] = target->x;
        out[0x1D] = target->position.bits.y;
        out[0x1E] = target->position.raw >> 15;
    } else {
        out[0x1C] = acting->action_target_x;
        out[0x1D] = acting->action_target_y;
        out[0x1E] = acting->action_target_elevation;
    }
}
