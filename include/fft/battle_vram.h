#ifndef FFT_BATTLE_VRAM_H
#define FFT_BATTLE_VRAM_H

#include "psx/gpu.h"
#include "psx/types.h"

/*
 * Two of these records back the battle EVTCHR/SP2 VRAM cache.  The event
 * SaveEVTCHR and LoadEVTCHR commands establish the header fields and the
 * 0x6400-byte image payload; every target access uses a 0x7564-byte stride.
 */
typedef struct battle_vram_slot {
    u32 owner;              /* 0x0000; 0xff free, 0xfe saved */
    u32 evtchr_load_marker; /* 0x0004 */
    u32 evtchr_load_state;  /* 0x0008 */
    RECT image_rect;        /* 0x000c */
    u8 padding_0014[0x1150];
    u8 image_data[0x6400]; /* 0x1164 */
} battle_vram_slot_t;

typedef char BattleVramSlot_size_must_be_0x7564[(sizeof(battle_vram_slot_t) == 0x7564) ? 1 : -1];

extern battle_vram_slot_t g_battle_vram_slots[];

#endif
