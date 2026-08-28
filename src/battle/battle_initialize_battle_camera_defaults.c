#include "psx/gte.h"
#include "psx/types.h"

extern void main_set_vector(VECTOR* vector, s32 x, s32 y, s32 z);
extern void main_set_svector(SVECTOR* vector, s16 x, s16 y, s16 z);

extern VECTOR g_battle_offset_screen_coords;
extern VECTOR g_battle_camera_zoom;
extern SVECTOR g_battle_camera_render_state;
extern VECTOR g_battle_current_real_coords;
extern s32 g_battle_casting_unit_id;
extern s32 g_battle_casting_misc_id;
extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_z;
extern s32 g_battle_cursor_y;
extern s32 g_map_rotation_action;
extern s32 g_battle_map_zoom_action;
extern s32 g_battle_map_zoom_target;
extern s32 g_battle_map_tilt_action;
extern s32 g_battle_map_tilt_target;
extern s32 g_battle_game_flow_running;

void battle_initialize_battle_camera_defaults(void) {
    main_set_vector(&g_battle_offset_screen_coords, 0x100, 0xA0, 0x280);
    main_set_vector(&g_battle_camera_zoom, 0x1000, 0x1000, 0x1000);
    main_set_svector(&g_battle_camera_render_state, 0x12E, 0xE00, 0);
    main_set_vector(&g_battle_current_real_coords, 0, 0, 0);

    g_battle_casting_unit_id = 0xFF;
    g_battle_casting_misc_id = 0xFF;
    g_battle_cursor_y = 0;
    g_battle_cursor_z = 0;
    g_battle_cursor_x = 0;
    g_map_rotation_action = 0;
    g_battle_map_zoom_action = 0;
    g_battle_map_zoom_target = 1;
    g_battle_map_tilt_action = 0;
    g_battle_map_tilt_target = 1;
    g_battle_game_flow_running = 0;
}
