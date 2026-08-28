#include "fft/battle.h"

extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void func_80072D8C(battle_misc_data_t* unit);
extern s32 battle_resume_attack_phase_control(void);
extern void battle_system_function_setup_routine(s32 a, s32 b, u8 c, s32 d, s32 e);
extern s32 g_customized_options;
extern s32 g_post_effect_msg_counter;

void battle_caster_post_effect_messages(void) {
    battle_misc_data_t* unit;

    unit = battle_get_casting_unit_misc_data();
    func_80072D8C(unit);
    if (g_customized_options & 0x180000) {
        g_post_effect_msg_counter = 0;
    }
    if (battle_resume_attack_phase_control() == 0) {
        battle_system_function_setup_routine(0xA, 0, unit->battle_data->misc_unit_id, 0, 0);
    }
}
