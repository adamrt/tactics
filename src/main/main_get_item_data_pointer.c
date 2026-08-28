#include "fft/data.h"

extern item_data_t g_primary_item_data[];

item_data_t* main_get_item_data_pointer(s32 item_id) {
    return &g_primary_item_data[item_id & 0xff];
}
