#include "psx/types.h"

extern s16 g_bunit_ability_entries[];
extern u8* g_bunit_selected_specific_ability;

s32 bunit_get_ability_ct_display_value(s32 index) {
    s32 ability;
    s32 result;

    ability = g_bunit_ability_entries[index];
    /* Fence (emits nothing): keeps the lh result as one SImode value. Without
     * it combine rewrites `(s16) >> 14` as `lhu / sll 16 / sra 30` and GCC
     * also grows an 8-byte frame; tried u16 array + (s16) cast, pointer-local
     * load, and hoisting the shift -- all reproduce the same wrong shape. */
    __asm__("" : "=r"(ability) : "0"(ability));
    result = 0x20000000;

    if ((ability & 0x2000) == 0) {
        s32 quotient;
        s32 remainder;

        result = g_bunit_selected_specific_ability[0x0c];
        quotient = 100 / result;
        remainder = 100 % result;
        result = quotient + (remainder != 0);
    }
    {
        s32 ability_type = ability >> 14;

        if (ability_type != 0) {
            result |= 0x40000000;
        }
    }
    return result;
}
