#ifndef FFT_STATUS_H
#define FFT_STATUS_H

#include "psx/types.h"

typedef struct status_effect_data {
    u8 unknown_00[2];
    u8 order;
    u8 ct;
    u8 flags_1;
    u8 flags_2;
    u8 unknown_06[10];
} status_effect_data_t;

typedef char StatusEffectData_size_must_be_0x10[(sizeof(status_effect_data_t) == 0x10) ? 1 : -1];

extern const status_effect_data_t g_status_effect_data[40];

#endif
