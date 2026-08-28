#ifndef FFT_ATTACK_H
#define FFT_ATTACK_H

#include "psx/types.h"

/* Twelve-byte deployment-area record used by EVENT/ATTACK.OUT. */
typedef struct attack_squad_data {
    u32 valid_tile_bitmap; /* 0x00; 5-by-5 deployment mask */
    s8 center_x;           /* 0x04 */
    s8 center_y;           /* 0x05 */
    u8 _pad_06;            /* 0x06 */
    u8 orientation_flags;  /* 0x07; original and rotated orientations */
    u8 unit_limit;         /* 0x08 */
    u8 map_id;             /* 0x09 */
    u16 placement_id;      /* 0x0a */
} attack_squad_data_t;

typedef char attack_squad_data_size_must_be_0x0c[(sizeof(attack_squad_data_t) == 0x0c) ? 1 : -1];

#endif
