#include "psx/types.h"

extern s16 D_801cd838;
extern s32 D_801cd668;
extern s32 D_801cd52c;

void world_bin_clear_some_data_in_0x801cd000_range(void) {
    D_801cd838 = 0;
    D_801cd668 = 0;
    D_801cd52c = 0;
}
