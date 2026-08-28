#include "psx/types.h"

extern u8 g_world_selected_card_slot;

/* Returns the memory card slot selected for world map save/load. */
u8 world_get_selected_card_slot(void) {
    return g_world_selected_card_slot;
}
