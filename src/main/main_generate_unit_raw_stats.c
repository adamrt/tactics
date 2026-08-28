#include "psx/types.h"

extern void generate_unit_base_raw_stats(u8* unit_data, s32 value);

void main_generate_unit_raw_stats(u8* unit_data) {
    s32 value;

    if ((unit_data[6] & 0x80) != 0) {
        value = 0;
    } else if ((unit_data[6] & 0x40) != 0) {
        value = 1;
    } else {
        value = 3;
    }
    generate_unit_base_raw_stats(unit_data + 0x72, value);
}
