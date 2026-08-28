#include "fft/data.h"

extern party_data_t* main_get_party_data_pointer(s32 index);

extern u8* D_801CD8C4;
extern s32 D_80189F6C;

void world_bin_generate_formation_unit_name_string(void) {
    u8* out;
    party_data_t* unit;
    s32 i;
    s32 j;
    u8 c;

    out = D_801CD8C4;
    for (i = 0; i < 0x14; i++) {
        unit = main_get_party_data_pointer(i);
        if (unit->party_id == PARTY_ID_NONE) {
            *out = 0xFE;
            out++;
        } else {
            for (j = 0; j < 0x10; j++) {
                c = unit->name[j];
                *out = c;
                if ((c & 0xFE) == 0xFE) {
                    out++;
                    break;
                }
                out++;
                if (j == 0xF) {
                    *out = 0xFE;
                    out++;
                }
            }
        }
    }
    D_80189F6C = D_80189F6C + 1;
}
