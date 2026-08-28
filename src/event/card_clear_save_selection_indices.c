#include "psx/types.h"

extern s16 g_card_selection_index;
extern s16 g_card_save_slot_index;

void card_clear_save_selection_indices(void) {
    g_card_selection_index = -1;
    g_card_save_slot_index = -1;
}
