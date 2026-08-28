#include "fft/data.h"

extern party_data_t g_party_data[];

party_data_t* main_get_party_data_pointer(s32 party_index) {
    party_data_t* party_data;

    if (party_index < 20) {
        party_data = &g_party_data[party_index];
    } else {
        party_data = 0;
    }
    return party_data;
}
