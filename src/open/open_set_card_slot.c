#include "psx/types.h"

extern u8 g_open_card_slot;

void open_set_card_slot(u8 slot) {
    g_open_card_slot = slot;
}
