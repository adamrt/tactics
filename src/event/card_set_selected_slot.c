#include "psx/types.h"

extern u8 g_card_selected_slot;

void card_set_selected_slot(s32 value) {
    g_card_selected_slot = value;
}
