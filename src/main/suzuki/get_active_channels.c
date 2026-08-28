#include "psx/types.h"

u32 SuzukiGetActiveChannels(void* music) {
    int remaining = *((u8*)music + 0x16);
    u8* channel = (u8*)music + 0xb8;
    u32 active = 0;

    do {
        if (*(u16*)channel != 0) {
            active |= *(u32*)(channel + 0x34);
        }
        remaining--;
        channel += 0x160;
    } while (remaining != 0);

    return active;
}
