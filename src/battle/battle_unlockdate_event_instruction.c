#include "psx/types.h"

extern void func_8013DA88(s32 arg0, s32 arg1, s32 arg2);

void battle_unlockdate_event_instruction(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 base;
    s32 i;
    s32 mask;

    base = arg1 * 9;
    mask = 1;
    i = 0;
    do {
        func_8013DA88(arg0, base + i, arg3 & (u8)mask);
        i++;
        mask *= 2;
    } while (i < 5);
    mask = 1;
    i = 0;
    do {
        s32 slot = i + 5;
        func_8013DA88(arg0, base + slot, arg2 & (u8)mask);
        i++;
        mask *= 2;
    } while (i < 4);
}
