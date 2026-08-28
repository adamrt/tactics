#include "fft/data.h"
#include "psx/types.h"

extern item_data_t g_primary_item_data[];

u16 world_get_item_price(s32 item_id) {
    return g_primary_item_data[item_id & 0x3ff].price;
}
