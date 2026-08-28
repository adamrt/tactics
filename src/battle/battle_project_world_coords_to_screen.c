#include "psx/types.h"

extern u8 g_battle_camera_matrix[];
extern u8 g_battle_camera_render_state[];
extern u8 g_battle_offset_screen_coords[];
extern u8 g_battle_camera_zoom[];

extern void battle_update_battle_camera_matrices(void* camera_matrix,
    void* render_state,
    void* offset_screen_coords,
    void* camera_zoom);
extern void func_8001D0A8(void* camera_matrix);
extern void func_8001D138(void* camera_matrix);
extern void func_8001D578(const void* world_coords, void* transformed_coords,
    void* result);

void battle_project_world_coords_to_screen(const void* world_coords,
    s16* screen_coords) {
    s32 transformed_coords[4];
    s32 result;

    battle_update_battle_camera_matrices(g_battle_camera_matrix,
        g_battle_camera_render_state,
        g_battle_offset_screen_coords,
        g_battle_camera_zoom);
    func_8001D0A8(g_battle_camera_matrix);
    func_8001D138(g_battle_camera_matrix);
    func_8001D578(world_coords, transformed_coords, &result);
    screen_coords[0] = transformed_coords[0];
    screen_coords[1] = transformed_coords[1];
}
