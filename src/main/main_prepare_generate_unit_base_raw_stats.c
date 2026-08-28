#include "psx/types.h"

extern void generate_unit_base_raw_stats(u8* unit_data);

void main_prepare_generate_unit_base_raw_stats(u8* unit_data) {
    generate_unit_base_raw_stats(unit_data + 0x19);
}
