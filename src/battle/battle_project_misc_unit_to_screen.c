#include "psx/types.h"

extern u8* battle_get_screen_data_ptr_by_misc_id(u32 misc_id);
extern void battle_project_world_coords_to_screen(const void* world_coords,
    s16* screen_coords);

void battle_project_misc_unit_to_screen(u32 misc_id, s16* screen_coords) {
    u8* screen_data;

    screen_data = battle_get_screen_data_ptr_by_misc_id(misc_id);
    if (screen_data != (u8*)-1) {
        battle_project_world_coords_to_screen(screen_data, screen_coords);
    }
}
