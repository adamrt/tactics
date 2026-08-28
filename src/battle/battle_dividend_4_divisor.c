#include "psx/types.h"

s32 battle_dividend_4_divisor(s32 divisor, s32 dividend) {
    if (divisor == 0) {
        return 0;
    }
    return dividend * 4 / divisor;
}
