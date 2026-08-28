#include "psx/types.h"

typedef struct MapAmbientLightColor {
    u8 data[4];
} MapAmbientLightColor;

extern MapAmbientLightColor g_map_ambient_light_color;
extern void transition_map_ambient_light_color(
    s32 frame_duration, const MapAmbientLightColor* color);

void battle_transition_and_store_map_ambient_light_color(
    s32 frame_duration, const MapAmbientLightColor* color) {
    transition_map_ambient_light_color(frame_duration, color);
    g_map_ambient_light_color = *color;
}
