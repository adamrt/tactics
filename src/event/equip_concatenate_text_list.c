#include "psx/types.h"

extern u8* func_801C8AC8(s32 arg0, s32 id, s32 arg2);

/* Concatenate the text for each entry of a -1 terminated id list into dst,
   optionally separating entries with 0xF8, and terminate with 0xFE. */
void equip_concatenate_text_list(s32 arg0, u8* dst, s16* list, s32 separate) {
    u8* src;
    s16* p;

    if (*list != -1) {
        p = list;
        do {
            src = func_801C8AC8(arg0, *(u16*)p & 0x7FF, 1);
            while (*src != 0xFE) {
                *dst = *src;
                src++;
                dst++;
            }
            p++;
            if (separate != 0) {
                *dst = 0xF8;
                dst++;
            }
        } while (*p != -1);
    }

    if (separate != 0) {
        dst--;
    }
    *dst = 0xFE;
}
