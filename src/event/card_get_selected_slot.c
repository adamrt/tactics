#include "psx/types.h"

extern u8 g_card_selected_slot;

u8 card_get_selected_slot(void) {
    return g_card_selected_slot;
}
