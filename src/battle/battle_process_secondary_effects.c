#include "psx/types.h"

typedef struct SecondaryEffectData {
    u8 previous_target_id;
    u8 _pad001[2];
    u8 function_id;
    u8 _pad004[80];
} SecondaryEffectData;

typedef s32 (*SecondaryEffectFunction)(void);

extern void* find_polygons_by_depth(void);
extern void remove_secondary_effect(u8 target_id);

extern SecondaryEffectFunction g_secondary_effect_functions[];
extern SecondaryEffectData g_secondary_effect_data[];
extern u16 g_previous_effect_target_id;
extern u32 g_current_effect_target_id;
extern s32 g_effect_buffer_index;
extern void* g_effect_polygon_depth_data;
extern SecondaryEffectData* g_current_secondary_effect;

s32 battle_process_secondary_effects(void) {
    SecondaryEffectData* effect;
    u32 previous_target_id;

    g_effect_polygon_depth_data = find_polygons_by_depth();
    g_effect_buffer_index = 1 - g_effect_buffer_index;
    g_current_effect_target_id = g_previous_effect_target_id;
    if (g_previous_effect_target_id == 0) {
        return 0;
    }

    do {
        effect = &g_secondary_effect_data[g_current_effect_target_id];
        g_current_secondary_effect = effect;
        previous_target_id = effect->previous_target_id;
        if (g_secondary_effect_functions[effect->function_id]() == 0) {
            remove_secondary_effect(g_current_effect_target_id);
        }
        g_current_effect_target_id = previous_target_id;
    } while (previous_target_id != 0);

    return 1;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
