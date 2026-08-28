#include "psx/types.h"

extern u8* func_801CB660(s32 arg0, s32 id, s32 arg2);

void bunit_concatenate_text_ids(s32 arg0, u8* out, s16* ids_arg, s32 sep) {
    s16* ids;
    u8* s;

    if (*ids_arg == -1) {
        goto done;
    }
    ids = ids_arg;
    do {
        s = func_801CB660(arg0, *ids & 0x7FF, 1);
        while (*s != 0xFE) {
            *out = *s;
            s++;
            out++;
        }
        ids++;
        if (sep != 0) {
            *out = 0xF8;
            out++;
        }
    } while (*ids != -1);
done:
    if (sep != 0) {
        out--;
    }
    *out = 0xFE;
}
