#include "fft/battle.h"
#include "psx/types.h"

/* View of battle_stats_t 0x16e..0x17f (action_actor_id through
 * action_target_y); the target keeps a second pointer biased to 0x16e. */
typedef struct ReflectAction {
    u8 actor_id;    /* 0x16e */
    u8 skillset_id; /* 0x16f */
    s16 ability_id; /* 0x170 */
    u8 pad172[6];
    u8 reaction_id;       /* 0x178 */
    u8 target_id;         /* 0x179 */
    s16 target_x;         /* 0x17a */
    s16 target_elevation; /* 0x17c */
    s16 target_y;         /* 0x17e */
} ReflectAction;

extern u8 D_80192DCC;
extern u8 D_80192DD0;
extern s32 func_8018F2B0(battle_stats_t*, s32, s32, s32, s32*, s32*, s32*);

s32 battle_reflect_targeting(battle_stats_t* unit) {
    ReflectAction* act;
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 last_attack;

    act = (ReflectAction*)&unit->action_actor_id;
    dx = unit->x - D_80192DCC;
    dy = unit->position.bits.y - D_80192DD0;
    if (dx == 0 && dy == 0) {
        return -1;
    }
    if (func_8018F2B0(unit, dx, dy, 0, &x, &y, &z) != 0) {
        return -1;
    }
    act->skillset_id = 0xB;
    last_attack = *(u16*)&unit->action.last_received_attack;
    act->reaction_id = 5;
    act->target_id = 0;
    act->ability_id = last_attack;
    act->target_x = x;
    act->target_y = y;
    act->target_elevation = z;
    return 0;
}
