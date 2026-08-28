#include "fft/map.h"

extern map_move_find_item_data_t g_current_map_move_find_item_data;

void battle_load_move_find_item_data(map_move_find_item_data_t* map_data) {
    g_current_map_move_find_item_data = *map_data;
}
