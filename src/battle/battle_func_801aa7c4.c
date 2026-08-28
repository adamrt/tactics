#include "psx/types.h"

void battle_func_801aa7c4(u8* obj, s32 value) {
    u16* flags = (u16*)(obj + 6);

    *flags = (*flags & 0xfff9) | (value & 6);
}
