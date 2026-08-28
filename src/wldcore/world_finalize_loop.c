#include "psx/types.h"

extern s32 g_system_flags;
extern void DrawSync(s32);
extern void VSync(s32);
extern void SetDispMask(s32);
extern void func_800911CC(void);
extern void main_unload_scenario_music_and_tunes(void);
extern void world_set_script_variable(s32, void*);
extern void* D_800BBC6C;

/* Finalize one WLDCORE loop pass and publish the world status. */
void world_finalize_loop(void) {
    DrawSync(0);
    VSync(0);
    SetDispMask(0);
    func_800911CC();
    if ((g_system_flags & 0x200000) == 0) {
        main_unload_scenario_music_and_tunes();
    }
    world_set_script_variable(0x33, D_800BBC6C);
}
