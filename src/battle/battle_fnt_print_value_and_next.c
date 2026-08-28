#include "psx/types.h"

extern const char g_battle_decimal_format[];
extern void FntPrint(const char* format, ...);

/* Append value and value + 1 to the active Psy-Q font stream. */
void battle_fnt_print_value_and_next(s32 value) {
    s32 saved_value = value;
    /* Pin: unpinned GCC homes the format string in $s0 and the value in $s1,
     * the reverse of the target (declaration order and dropping the value
     * copy do not change it). */
    register const char* format __asm__("$17") = g_battle_decimal_format;

    FntPrint(format, saved_value);
    FntPrint(format, saved_value + 1);
}
