#include "psx/types.h"

extern u8* g_battle_data;
extern u8 g_battle_buffer_a[];
extern void ClearOTagR(u32* otag, int length);

void main_put_otag(void) {
    u8* battle_data = g_battle_buffer_a;
    u32* otag;

    if (g_battle_data == battle_data) {
        battle_data += 0xee28;
    }
    otag = *(u32**)(battle_data + 0xe5b4);
    g_battle_data = battle_data;
    ClearOTagR(otag, 0x180);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
