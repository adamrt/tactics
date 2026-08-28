#include "psx/gpu.h"
#include "psx/types.h"

extern POLY_FT4 g_attack_frame_ft4[];

extern void battle_make_default_poly_ft4(POLY_FT4* poly);

void attack_out_initialise_frame_ft4_array(void) {
    s32 i = 0;
    s32 offset = sizeof(POLY_FT4);
    POLY_FT4* base = g_attack_frame_ft4;
    POLY_FT4* odd = base + 1;
    POLY_FT4* even = base;

    do {
        battle_make_default_poly_ft4(even);
        battle_make_default_poly_ft4(odd);
        *(u16*)((u8*)g_attack_frame_ft4 + offset - 0x12) = GetTPage(0, 0, 0x140, 0);
        *(u16*)((u8*)g_attack_frame_ft4 + offset + 0x16) = GetTPage(0, 2, 0x3c0, 0x100);
        SetSemiTrans(odd, 1);
        offset += sizeof(POLY_FT4) * 2;
        odd += 2;
        i += 2;
        even += 2;
    } while (i < 10);
}
