#include "psx/types.h"

extern s32 func_80133158(s32);
extern void func_8014CEB4(s32);
extern s32 battle_get_battle_unit_index_by_misc_id(s32);
extern void battle_set_specific_unit_animation_value_when_battle_init(s32, s32);
extern void battle_prepare_misc_unit_palette_modulation(s32, s32, s32, s32, s32);
extern void battle_thread_wait(s32);
extern void battle_set_unit_cannot_exist_return_r2_0(s32);
extern void battle_teleport_effect_callback(void);
extern s32 g_sound_effect_id_to_play;
extern void (*g_call_inner_subroutine_target)(void);

void battle_teleportout_event_instruction(s32 arg, s32 remove) {
    s32 misc;
    s32 idx;

    misc = func_80133158(arg);
    if (misc == 0x7D0) {
        return;
    }
    g_sound_effect_id_to_play = 0x6A;
    g_call_inner_subroutine_target = battle_teleport_effect_callback;
    func_8014CEB4(misc);
    idx = battle_get_battle_unit_index_by_misc_id(misc);
    battle_set_specific_unit_animation_value_when_battle_init(misc, 0x1B);
    battle_prepare_misc_unit_palette_modulation(misc, 2, 0x1F, 0x1F, 0x1F);
    battle_thread_wait(0x3C);
    battle_prepare_misc_unit_palette_modulation(misc, 2, -0x1F, -0x1F, -0x1F);
    battle_thread_wait(0x3C);
    if (remove != 0) {
        battle_set_unit_cannot_exist_return_r2_0(idx);
    }
}
