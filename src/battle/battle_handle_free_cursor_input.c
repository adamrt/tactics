#include "fft/battle.h"

extern void update_all_unit_rotation_and_vectors(void);
extern void battle_update_and_animate_units(void);
extern void update_status_bubbles_and_graphics(void);
extern void battle_calculate_tile_coords_and_glow_from_at_list(void);
extern s32 g_status_screen_selected;

void battle_handle_free_cursor_input(void) {
    update_all_unit_rotation_and_vectors();
    if (g_status_screen_selected != 1) {
        battle_update_and_animate_units();
    }
    update_status_bubbles_and_graphics();
    battle_calculate_tile_coords_and_glow_from_at_list();
}
