#include "fft/data.h"

extern party_data_t* main_get_party_data_pointer(s32 party_index);
extern u8 g_inventory[];

s32 require_restore_party_item_counts(s32 party_index) {
    party_data_t* party = main_get_party_data_pointer(party_index);
    s32 index = 0;

    do {
        u8 item_id = party->equipment[index];

        index++;
        if ((item_id != 0) && (item_id != 0xff)) {
            g_inventory[item_id]++;
        }
    } while (index < 7);
    return 0;
}
