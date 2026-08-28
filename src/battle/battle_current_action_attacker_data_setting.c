#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern u8 g_current_ability_attacker_facing;
extern u8 D_8019389D;
extern u8 D_8019389E;
extern u8 D_8019389F;
extern u8 D_801938A0;
extern s16 D_801938A2;
extern s16 D_801938A4;
extern u8 D_801938A6[];

extern void main_copy_action_data(const u8* src, u8* dst);

void battle_current_action_attacker_data_setting(battle_stats_t* unit) {
    battle_stats_t* target;
    s32 x;
    s32 y;

    if (unit->job_id == 0x5D) {
        return;
    }
    main_copy_action_data(&unit->action_actor_id, D_801938A6);
    if (unit->action_reaction_id == 6) {
        target = &battle_stats[unit->action_target_id];
        x = target->x;
        y = target->position.bits.y;
    } else {
        /* The target reads only the low byte (lbu) of the s16 target
         * coordinates here. */
        x = *(u8*)&unit->action_target_x;
        y = *(u8*)&unit->action_target_y;
    }
    D_801938A2 = x - unit->x;
    D_801938A4 = y - unit->position.bits.y;
    /* Read through a cast pointer, not position.raw: GCC 2.6.3 assumes a
     * struct-member load cannot alias the scalar global stores above and
     * hoists it past them; the target keeps source order. */
    g_current_ability_attacker_facing = (*(u16*)&unit->position >> 8) & 0xF;
    D_801938A0 = unit->team_flags & BATTLE_TEAM_MASK;
    D_8019389E = unit->equipment[3];
    D_8019389F = unit->equipment[5];
    D_8019389D = 1;
}
