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

void attack_render_signed_decimal_entries(s32 arg0, AttackGaugeEntry* entries,
    AttackGaugeOutput* out, s32 count) {
    /* Pin: the target keeps the counter in $s2 and `entries` in $s3; unpinned
     * GCC swaps them, and no declaration order or walking-pointer form
     * (3 variants tried) moves the allocator. */
    register s32 i __asm__("$18") = 0;
    s32 unused[2];

    if (count > 0) {
        do {
            s32 amount = *entries->value;

            out->x = entries->x;
            out->y = entries->y;
            entries->flags &= 0xf3ff;
            if (amount < 0) {
                out->color = 0x88888888;
                amount = -amount;
                entries->flags |= 0x800;
            } else if (amount > 0) {
                out->color = 0xcccccccc;
                entries->flags |= 0x400;
            } else {
                out->color = 0;
                entries->flags |= 0x800;
            }
            {
                s32 flags = entries->flags;
                entries++;
                i++;
                func_801C1650(amount, flags, arg0, out);
            }
            out->color = 0;
        } while (i < count);
    }
}
