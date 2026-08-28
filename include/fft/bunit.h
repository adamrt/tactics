#ifndef FFT_BUNIT_H
#define FFT_BUNIT_H

#include "psx/types.h"

/*
 * Documented prefix of the BUNIT.OUT unit-data record. This is the
 * formation/menu representation, not party_data_t, entd_unit_t, or BattleStats.
 * Its full size has not yet been established.
 */
typedef struct bunit_unit_data {
    u8 _pad00[4];
    u8 gender_flags; /* 0x04; bits 0x40/0x80 are job restrictions */
    u8 _pad05[0x1f];
    s16 monster_base_job_id; /* 0x24; used when job_id is 0x82 */
    u8 _pad26[0x3e];
    u8 job_levels[10]; /* 0x64; packed job levels */
    u8 _pad6e[6];
    u8 job_id; /* 0x74 */
} bunit_unit_data_t;

typedef char bunit_unit_data_job_id_must_be_0x74[((unsigned long)&((bunit_unit_data_t*)0)->job_id == 0x74) ? 1 : -1];

#endif
