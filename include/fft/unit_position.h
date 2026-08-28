#ifndef FFT_UNIT_POSITION_H
#define FFT_UNIT_POSITION_H

#include "psx/types.h"

/*
 * Packed Y and facing data shared by ENTD definitions and runtime battle
 * records.  The US target copies the named bit groups independently.
 */
typedef union battle_unit_position {
    u16 raw;
    struct {
        u16 y : 8;
        u16 facing : 4;
        u16 flags_12_13 : 2;
        u16 _bit14 : 1;
        u16 higher_elevation : 1;
    } bits;
} battle_unit_position_t;

typedef char BattleUnitPosition_size_must_be_2[(sizeof(battle_unit_position_t) == 2) ? 1 : -1];

typedef union entd_unit_position {
    u16 raw;
    struct {
        u16 y : 8;
        u16 facing : 2;
        u16 _bits10_11 : 2;
        u16 flags_12_13 : 2;
        u16 _bit14 : 1;
        u16 higher_elevation : 1;
    } bits;
} entd_unit_position_t;

typedef char ENTDUnitPosition_size_must_be_2[(sizeof(entd_unit_position_t) == 2) ? 1 : -1];

#endif
