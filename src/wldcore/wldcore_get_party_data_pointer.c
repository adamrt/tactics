#include "fft/data.h"

extern party_data_t* main_get_party_data_pointer(s32 party_index);

party_data_t* wldcore_get_party_data_pointer(s32 party_index) {
    return main_get_party_data_pointer(party_index);
}
