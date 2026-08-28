#include "psx/types.h"

extern const u16 g_zodiac_day_limits[12];

u16 main_calculate_zodiac_symbol(u32 birthday) {
    s32 zodiac;
    /* Pinned: as a pseudo, GCC reverses this loop into a count-down. The
     * explicit value/12 below reproduces the target's temp allocation. */
    register s32 index __asm__("$6");
    s32 sign;
    s32 value;
    const u16* day_limit;
    u16 day;

    zodiac = 0;
    index = 0;
    birthday &= 0xffff;
    day_limit = g_zodiac_day_limits;

    while (index < 12) {
        day = *day_limit;
        __asm__("" : : "r"(day));
        index++;
        day_limit++;
        zodiac += birthday >= day;
    }
    value = zodiac + 9;
    zodiac = value / 12;
    sign = value >> 31;
    return value - zodiac * 12;
}
