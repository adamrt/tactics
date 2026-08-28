#include "psx/types.h"

extern u8 g_body_part_seq_data[];

u8* battle_get_body_part_seq_data(void) {
    return g_body_part_seq_data;
}
