#include "psx/types.h"

extern s32 effect_stage_processing(void);
extern s32 battle_process_secondary_effects(void);
extern void update_effect_camera_rotation_and_zoom(void);

s32 battle_process_effect_cycle(void) {
    s32 stage_result;
    s32 related_result;

    stage_result = effect_stage_processing();
    related_result = battle_process_secondary_effects();
    update_effect_camera_rotation_and_zoom();

    if (stage_result != 0 || related_result != 0) {
        return 1;
    }
    return 0;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
