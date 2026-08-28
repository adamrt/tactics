#include "psx/types.h"

typedef struct AttackGaugeEntry {
    u16 x;
    u16 y;
    s16* value;
    s16 flags;
    s16 pad;
} AttackGaugeEntry;

typedef struct AttackGaugeOutput {
    u16 x;
    u16 y;
    u8 reserved_04[8];
    u32 color;
} AttackGaugeOutput;

extern void func_801C1650(s32 amount, s32 flags, s32 arg2,
    AttackGaugeOutput* out);

void attack_render_decimal_entry_list(s32 arg0, AttackGaugeEntry* entries,
    AttackGaugeOutput* out, s32 count) {
    /* Pin: the target keeps the counter in $s2 and `entries` in $s3; unpinned
     * GCC swaps them (same as the 0x801c1450 twin). */
    register s32 i __asm__("$18") = 0;
    s32 unused[2];

    if (count > 0) {
        do {
            s32 amount = *entries->value;
            s32 flags;

            out->x = entries->x;
            out->y = entries->y;
            flags = entries->flags;
            flags &= 0xf3ff;
            if (amount < 0) {
                amount = -amount;
                flags |= 0x800;
                out->color = 0x77777777;
            } else if (amount > 0) {
                flags |= 0x400;
                out->color = 0xbbbbbbbb;
            } else {
                out->color = 0;
                flags &= 0xfff0;
                flags |= 0x804;
            }
            func_801C1650(amount, flags, arg0, out);
            entries++;
            i++;
            out->color = 0;
        } while (i < count);
    }
}
