#include "fft/data.h"

extern party_data_t g_party_data[];

s32 main_find_party_slot_by_sprite_set(s32 sprite_set) {
    s32 party_index = 0;
    s32 empty_party_id = 0xff;
    party_data_t* party_data = g_party_data;

    while (party_index < 20) {
        if (party_data->party_id != empty_party_id && party_data->sprite_set == sprite_set) {
            return party_index;
        }
        party_index++;
        party_data++;
    }

    return -1;
}
