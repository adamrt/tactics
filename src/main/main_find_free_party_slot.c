#include "fft/data.h"

extern party_data_t* main_get_party_data_pointer(s32 party_index);

s32 main_find_free_party_slot(s32 save_formation, u8* palette) {
    party_data_t* party_data[20];
    s32 party_index;
    s32 start_index;
    s32 limit;

    *palette = 0;

    for (party_index = 0; party_index < 20; party_index++) {
        party_data[party_index] = main_get_party_data_pointer(party_index);
    }

    if (save_formation != 0) {
        start_index = 16;
        limit = 20;
    } else {
        start_index = 0;
        limit = 16;
    }

    party_index = start_index;

    while (party_index < limit) {
        if (party_data[party_index]->party_id == 0xff) {
            return party_index;
        }
        party_index++;
    }

    return -1;
}
