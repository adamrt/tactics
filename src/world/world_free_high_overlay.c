extern void* g_high_overlay_load_address;
extern void main_game_free(void* ptr);

void world_free_high_overlay(void) {
    main_game_free(g_high_overlay_load_address);
}
