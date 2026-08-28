#include "fft/battle.h"

extern battle_display_unit_t* battle_get_unit_misc_data_by_misc_id(u16);
extern battle_display_unit_t* battle_get_casting_unit_misc_data(void);
extern void set_target_anim_from_attack_type(battle_display_unit_t*, battle_display_unit_t*);

s32 battle_set_target_anim_by_misc_id(u16 misc_id) {
    battle_display_unit_t* target = battle_get_unit_misc_data_by_misc_id(misc_id);
    battle_display_unit_t* caster = battle_get_casting_unit_misc_data();

    set_target_anim_from_attack_type(caster, target);
    return 1;
}
