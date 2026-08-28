#include "psx/types.h"

extern s32 D_801cd080;

s32 world_add_to_fitting_room_cost(s32 delta) {
    return D_801cd080 = delta + D_801cd080;
}
