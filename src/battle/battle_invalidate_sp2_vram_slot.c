#include "fft/battle_vram.h"

typedef struct BattleMiscDataHeader {
    u8 padding[4];
    u8 entd_id;
} BattleMiscDataHeader;

void battle_invalidate_sp2_vram_slot(BattleMiscDataHeader* unit) {
    u32 invalid;
    u8* slot;
    s32 count;

    count = 0;
    invalid = 0xff;
    slot = (u8*)g_battle_vram_slots;
    do {
        u32 descriptor = *(u32*)slot;

        count++;
        if (((descriptor & 0x1f) == unit->entd_id) && ((descriptor & 0x40) != 0)) {
            *(u32*)slot = invalid;
        }
        slot += 0x7564;
    } while (count < 2);
}
