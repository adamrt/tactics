#include "psx/types.h"

extern const u8 g_open_month_lengths[12];

s32 open_calculate_birthday_day_index(s32 month, s32 day) {
    s32 index;
    s32 elapsed_days;
    s32 result;

    month--;
    elapsed_days = 0;
    index = 0;
    while (index < month) {
        elapsed_days += g_open_month_lengths[index];
        index++;
    }

    result = elapsed_days - 1;
    return result + day;
}
