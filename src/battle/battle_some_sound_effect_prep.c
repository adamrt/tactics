#include "psx/types.h"

extern u8* g_effect_data_ptrs[];
extern u8* g_effect_sound_section_ptr;
extern s32 D_801BC0DC;

extern void func_80017EB8(u8*);
extern void SuzukiAppendVFXSMD(u8*);

void battle_some_sound_effect_prep(s16 index) {
    u8* base;
    s32 offset;

    if (g_effect_sound_section_ptr != 0) {
        func_80017EB8(g_effect_sound_section_ptr);
    }

    base = g_effect_data_ptrs[index];
    offset = *(s32*)(base + 0x20);
    if (offset != 0) {
        g_effect_sound_section_ptr = base + offset;
        SuzukiAppendVFXSMD(base + offset);
        D_801BC0DC = *(u16*)(g_effect_sound_section_ptr + 0xA) << 16;
    } else {
        g_effect_sound_section_ptr = 0;
        D_801BC0DC = 0;
    }
}
