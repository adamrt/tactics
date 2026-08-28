#include "psx/types.h"

extern u8 g_attack_valid_deployment_tiles[5][5];

u8 attack_get_valid_deployment_tile(s32 column, s32 row) {
    return g_attack_valid_deployment_tiles[row][column];
}
