#include "psx/types.h"

extern s16 g_jobstts_ability_entries[];
extern u16 g_ability_data[][4];

u32 jobstts_get_ability_jp_cost_display_value(s32 index) {
    s32 value;
    /* Pin: with the fence below, `result` must also live in $v1 or GCC falls
     * back to the same lhu/sll/sra shape (pin-only removal re-verified). */
    register u32 result __asm__("$3");

    value = g_jobstts_ability_entries[index];
    /* Fence (emits nothing): keeps the lh result as one SImode value. Without
     * it combine rewrites `(s16) >> 14` as `lhu / sll 16 / sra 30` and GCC
     * also grows an 8-byte frame; tried u16 array + (s16) cast, pointer-local
     * load, and hoisting the shift -- all reproduce the same wrong shape. */
    __asm__("" : "=r"(value) : "0"(value));
    result = 0x20000000;
    if (!(value & 0x2000)) {
        s32 ability_id = value & 0x3ff;

        result = g_ability_data[ability_id][0];
    }
    {
        s32 ability_type = value >> 14;

        if (ability_type != 0) {
            result |= 0x40000000;
        }
    }
    return result;
}
