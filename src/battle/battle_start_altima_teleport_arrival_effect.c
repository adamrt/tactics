#include "fft/battle.h"

enum {
    EFFECT_ALTIMA_HOLY_ANGEL_TELEPORT_ARRIVAL_0B8 = 0xb8,
    EFFECT_ALTIMA_ARCH_ANGEL_TELEPORT_ARRIVAL_028 = 0x28,
};

extern void battle_initialize_altima_teleport_data(
    battle_misc_data_t* unit, u8* teleport_data);
extern void ability_animation(s32 unused, s32 effect_id, u8* effect_data);
extern void battle_set_secondary_effect_teleport(battle_misc_data_t* unit);
extern void main_play_sound_find_channel(s32 sound_id);

s32 battle_start_altima_teleport_arrival_effect(battle_misc_data_t* unit) {
    u8 teleport_data[200];
    s32 animation_type;
    s32 effect_id;

    battle_initialize_altima_teleport_data(unit, teleport_data);
    if (unit->spritesheet_id == 0x41) {
        goto holy_angel;
    }
    animation_type = 0;
    if (unit->spritesheet_id == 0x49) {
        goto arch_angel;
    }
    goto fallback;

holy_angel:
    animation_type = 0;
    effect_id = EFFECT_ALTIMA_HOLY_ANGEL_TELEPORT_ARRIVAL_0B8;
    goto animate;

arch_angel:
    effect_id = EFFECT_ALTIMA_ARCH_ANGEL_TELEPORT_ARRIVAL_028;

animate:
    ability_animation(animation_type, effect_id, teleport_data);
    return 1;

fallback:
    battle_set_secondary_effect_teleport(unit);
    main_play_sound_find_channel(0x6b);
    return 0;
}
