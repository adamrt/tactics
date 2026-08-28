#include "fft/battle_vram.h"

s32 battle_save_evtchr_slot(s32 slot_index) {
    s32 slot_offset;

    slot_offset = slot_index * 0x7564;
    if (*(u32*)((u8*)g_battle_vram_slots + slot_offset) == 0xff) {
        LoadImage((RECT*)((u8*)&g_battle_vram_slots[0].image_rect + slot_offset),
            (u32*)((u8*)g_battle_vram_slots[0].image_data + slot_offset));
        *(u32*)((u8*)g_battle_vram_slots + slot_offset) = 0xfe;
        return 1;
    }

    return 0;
}
