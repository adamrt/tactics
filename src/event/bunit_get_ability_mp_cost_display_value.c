#include "psx/types.h"

extern s16 g_bunit_ability_entries[];
extern u8* g_bunit_selected_specific_ability;

u32 bunit_get_ability_mp_cost_display_value(s32 index) {
    s32 value;
    /* Pin: with the fence below, `result` must also live in $v1 or GCC falls
     * back to the same lhu/sll/sra shape (pin-only removal re-verified). */
    register u32 result __asm__("$3");

    value = g_bunit_ability_entries[index];
    /* Emits no code; preserves the retail value register across the branch. */
    /* Fence (emits nothing): keeps the lh result as one SImode value. Without
     * it combine rewrites `(s16) >> 14` as `lhu / sll 16 / sra 30` and GCC
     * also grows an 8-byte frame; tried u16 array + (s16) cast, pointer-local
     * load, and hoisting the shift -- all reproduce the same wrong shape. */
    __asm__("" : "=r"(value) : "0"(value));
    result = 0x20000000;
    if ((value & 0x2000) == 0) {
        result = g_bunit_selected_specific_ability[0x0d];
    }
    {
        s32 ability_type = value >> 14;

        if (ability_type != 0) {
            result |= 0x40000000;
        }
    }
    return result;
}
