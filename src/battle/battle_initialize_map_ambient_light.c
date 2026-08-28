#include "psx/types.h"

typedef struct MapAmbientLightColor {
    u8 data[4];
} MapAmbientLightColor;

extern u8* get_map_record_data(s32 section_id, s32 map_id);
extern MapAmbientLightColor g_map_ambient_light_color;
extern s32 g_map_ambient_light_red;
extern s32 g_map_ambient_light_green;
extern s32 g_map_ambient_light_blue;

void battle_initialize_map_ambient_light(s32 unused_0, s32 unused_1, s32 map_id) {
    /* Pin: the target copies the record pointer into $a2 (`move a2,v0`);
     * unpinned GCC uses $v0 directly (124 bytes), and reusing the map_id
     * parameter for it does not produce the copy either. */
    register u8* color asm("$6");

    color = get_map_record_data(0x5d, map_id);
    asm volatile("" : "=r"(color) : "0"(color));
    g_map_ambient_light_color = *(MapAmbientLightColor*)color;
    g_map_ambient_light_red = color[0] << 16;
    g_map_ambient_light_green = color[1] << 16;
    g_map_ambient_light_blue = color[2] << 16;
}
