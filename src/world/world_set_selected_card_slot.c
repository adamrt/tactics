#include "psx/types.h"

extern u8 g_world_selected_card_slot;

/* Selects the memory card slot the world map save/load routines talk to. */
void world_set_selected_card_slot(u8 slot) {
    g_world_selected_card_slot = slot;
}
