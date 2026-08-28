#include "psx/gpu.h"

extern u8* g_effect_data_ptrs[];
extern u8* D_801BBF80;
extern void battle_load_map_palette_data(u8* dst, s32 arg1, s32 arg2, s32 arg3);

void battle_effect_palette_setup(s16 index) {
    RECT rect;
    u8* base;
    u8* data;
    s32 size;
    s32 raw_size;
    s32 height;

    base = g_effect_data_ptrs[index];
    data = base + *(s32*)(base + 0x24);
    D_801BBF80 = data;
    battle_load_map_palette_data(data, 0xC, 0, 1);
    battle_load_map_palette_data(data + 0x200, 0xD, 0, 1);
    raw_size = data[0x400] + (data[0x401] << 8);
    raw_size = (data[0x402] << 16) + raw_size;
    height = raw_size;
    size = height;
    if (data[0x403] != 0) {
        height = size / 0x100;
        rect.x = 0x180;
        rect.y = 0;
        rect.w = 0x80;
        rect.h = height;
        LoadImage(&rect, (u32*)(data + 0x404));
    } else {
        height = size;
        height = height / 0x80;
        rect.x = 0x180;
        rect.y = 0;
        rect.w = 0x40;
        rect.h = height;
        LoadImage(&rect, (u32*)(data + 0x404));
    }
}
