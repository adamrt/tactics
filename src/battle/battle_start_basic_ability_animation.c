#include "psx/types.h"

extern void ability_animation(s32 animation_type, s32 effect_id,
    u8* effect_data);

void battle_start_basic_ability_animation(s32 effect_id) {
    u8 effect_data[200];

    *(u16*)&effect_data[0] = 1;
    *(u16*)&effect_data[0xA4] = 0;
    effect_data[0xA6] = 0;
    *(u16*)&effect_data[4] = 0;
    effect_data[6] = 1;
    effect_data[7] = 0;
    effect_data[2] = 0;
    ability_animation(0, effect_id, effect_data);
}
