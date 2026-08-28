#include "psx/types.h"

u32 SuzukiGetMusicPlaying(void* music) {
    return *(u16*)((u8*)music + 0x10) >> 15;
}
