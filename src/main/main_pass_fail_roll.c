#include "psx/types.h"

extern s32 rand(void);

s32 main_pass_fail_roll(s32 maximum, s32 threshold) {
    s32 roll = rand() * maximum / 0x8000;

    return roll >= threshold;
}
