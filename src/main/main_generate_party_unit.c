#include "fft/data.h"

extern party_data_t* main_get_party_data_pointer(s32 party_index);
extern void generate_out_of_battle_unit(party_data_t* party_data, s32 unit_type);

s32 main_generate_party_unit(s32 unit_type) {
    party_data_t* party_data[20];
    s32 party_index;
    s32 palette = 0;

    for (party_index = 0; party_index < 20; party_index++) {
        party_data[party_index] = main_get_party_data_pointer(party_index);
    }

    for (party_index = 0; party_index < 16; party_index++) {
        if (party_data[party_index]->party_id == 0xff) {
            party_data[party_index]->party_id = party_index;
            party_data[party_index]->palette = palette;
            generate_out_of_battle_unit(party_data[party_index], unit_type);
            return party_index;
        }
    }

    return -1;
}
