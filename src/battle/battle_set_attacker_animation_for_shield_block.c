#include "fft/battle.h"

extern u8 g_spritesheet_data[];
extern void battle_store_unit_animation_facing_movement_data(u32 animation, s16 facing, u8* unit);

void battle_set_attacker_animation_for_shield_block(battle_misc_data_t* attacker, battle_misc_data_t* target) {
    battle_stats_t* stats;
    s32 kind;
    s32 anim;

    stats = target->battle_data;
    if (stats == 0) {
        return;
    }
    if (g_spritesheet_data[attacker->spritesheet_id * 4] >= 2) {
        return;
    }
    kind = stats->action.miss_type;
    anim = 0;
    if (kind >= 2 && (kind < 4 || kind == 0xA)) {
        switch (attacker->encoded_animation >> 1) {
        case 0x3D:
            anim = 0x5E;
            break;
        case 0x3E:
            anim = 0x5F;
            break;
        case 0x3F:
            anim = 0x60;
            break;
        case 0x40:
            anim = 0x5B;
            break;
        case 0x41:
            anim = 0x5C;
            break;
        case 0x42:
            anim = 0x5D;
            break;
        case 0x4D:
            anim = 0x61;
            break;
        case 0x4E:
            anim = 0x62;
            break;
        case 0x4F:
            anim = 0x63;
            break;
        }
    }
    if (anim != 0) {
        battle_store_unit_animation_facing_movement_data(anim, attacker->facing, (u8*)attacker);
    }
}
