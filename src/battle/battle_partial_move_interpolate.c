#include "psx/types.h"

void battle_partial_move_interpolate(s32* arg0, s32 arg1) {
    arg0[10] = (arg1 * arg0[10]) / 4096;
    arg0[11] = (arg1 * arg0[11]) / 4096;
    arg0[12] = (arg1 * arg0[12]) / 4096;
}
