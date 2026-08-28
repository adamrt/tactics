#include "psx/types.h"

extern s32 world_get_misc_id(s32 unit_id);
extern void world_call_inner_subroutine_on_main_thread(s32 misc_id);
extern s32 battle_teleport_effect_callback(u32 misc_id);

extern s32 (*g_world_inner_subroutine_callback)(u32 misc_id);

void world_teleport_unit_in(s32 unit_id) {
    s32 misc_id;

    misc_id = world_get_misc_id(unit_id);
    if (misc_id != 2000) {
        g_world_inner_subroutine_callback = battle_teleport_effect_callback;
        world_call_inner_subroutine_on_main_thread(misc_id);
    }
}
