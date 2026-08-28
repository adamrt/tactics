#include "fft/battle.h"
#include "psx/types.h"

/* The tail of a battle_ai_action_data_t (offset 0x1c): callers pass
 * `&action->mount_info`.  The priority is compared signed here. */
typedef struct {
    u8 mount_info;
    u8 base_hit_percent;
    s16 priority;
} BattleAiActionRank;

/* 2 if `a` ranks above `b`, 0 if below, 1 if equal. */
s32 battle_compare_target_priority_and_hit_rate(BattleAiActionRank* a, BattleAiActionRank* b) {
    u8 mount_a, mount_b;
    s16 priority_a, priority_b;
    u8 hit_a, hit_b;

    mount_a = a->mount_info;
    mount_b = b->mount_info;
    if (mount_a > mount_b)
        return 2;
    if (mount_a < mount_b)
        return 0;
    priority_a = a->priority;
    priority_b = b->priority;
    if (priority_a > priority_b)
        return 2;
    if (priority_a < priority_b)
        return 0;
    hit_a = a->base_hit_percent;
    hit_b = b->base_hit_percent;
    if (hit_a > hit_b)
        return 2;
    if (hit_a < hit_b)
        return 0;
    return 1;
}
