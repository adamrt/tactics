#include "psx/types.h"

typedef struct MapDarknessColor {
    u8 data[4];
} MapDarknessColor;

extern MapDarknessColor g_map_darkness_color;
extern void transition_map_darkness_color(
    s32 frame_duration, const MapDarknessColor* color);

void battle_transition_and_store_map_darkness_color(
    s32 frame_duration, const MapDarknessColor* color) {
    transition_map_darkness_color(frame_duration, color);
    g_map_darkness_color = *color;
}
