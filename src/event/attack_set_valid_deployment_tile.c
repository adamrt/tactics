#include "psx/types.h"

extern u8 g_attack_valid_deployment_tiles[5][5];

void attack_set_valid_deployment_tile(s32 column, s32 row, u8 is_valid) {
    g_attack_valid_deployment_tiles[row][column] = is_valid;
}
