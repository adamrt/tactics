#include "psx/types.h"

extern u8* D_80173C78;

void battle_clear_some_staging_data(void) {
    s32 i;
    for (i = 0; i < 21; i++) {
        (D_80173C78 + i)[0x39c] = 0;
        (D_80173C78 + i)[0x3b1] = 0;
    }
}
