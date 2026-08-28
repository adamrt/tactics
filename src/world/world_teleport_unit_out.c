#include "psx/types.h"

extern s32 world_get_misc_id(s32 unit_id);
extern void world_call_inner_subroutine_on_main_thread(s32 misc_id);
extern s32 get_unit_id_from_misc_id(s32 misc_id);
extern void world_set_unit_animation(s32 misc_id, s32 value);
extern void battle_prepare_misc_unit_palette_modulation(s32 misc_id, s32 mode, s32 x, s32 y, s32 z);
extern void world_wait(s32 frames);
extern void set_unit_cannot_exist(s32 unit_index);
extern s32 battle_teleport_effect_callback(u32 misc_id);

extern s32 g_world_sound_effect_id_to_play;
extern s32 (*g_world_inner_subroutine_callback)(u32 misc_id);

void world_teleport_unit_out(s32 unit_id, s32 remove_unit) {
    s32 misc_id;
    s32 unit_index;

    misc_id = world_get_misc_id(unit_id);
    if (misc_id != 2000) {
        g_world_sound_effect_id_to_play = 0x6a;
        g_world_inner_subroutine_callback = battle_teleport_effect_callback;
        world_call_inner_subroutine_on_main_thread(misc_id);
        unit_index = get_unit_id_from_misc_id(misc_id);
        world_set_unit_animation(misc_id, 0x1b);
        battle_prepare_misc_unit_palette_modulation(misc_id, 2, 0x1f, 0x1f, 0x1f);
        world_wait(0x3c);
        battle_prepare_misc_unit_palette_modulation(misc_id, 2, -0x1f, -0x1f, -0x1f);
        world_wait(0x3c);
        if (remove_unit != 0) {
            set_unit_cannot_exist(unit_index);
        }
    }
}
