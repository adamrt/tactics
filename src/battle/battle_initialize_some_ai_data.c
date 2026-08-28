#include "psx/types.h"

void battle_initialize_some_ai_data(u8* arg0) {
    *(s16*)(arg0 + 0x1E) = -0x7FFF;
    arg0[0x1C] = 0;
    arg0[0x1D] = 0;
    arg0[0x3] = 5;
    arg0[0x1] = 0;
}
