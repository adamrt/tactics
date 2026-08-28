#include "psx/types.h"

typedef struct UnalignedColorWord {
    u8 data[4];
} UnalignedColorWord;

typedef struct MapBackgroundGradientColors {
    UnalignedColorWord first;
    UnalignedColorWord second;
} MapBackgroundGradientColors;

extern UnalignedColorWord g_map_background_gradient_first;
extern UnalignedColorWord g_map_background_gradient_second;
extern void transition_map_background_gradient(
    s32 frame_duration, const MapBackgroundGradientColors* colors);

void battle_transition_and_store_map_background_gradient(
    s32 frame_duration, const MapBackgroundGradientColors* colors) {
    transition_map_background_gradient(frame_duration, colors);
    g_map_background_gradient_first = colors->first;
    g_map_background_gradient_second = colors->second;
}
