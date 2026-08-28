#include "psx/types.h"

extern s32 card_wait_for_operation_result(s32 retry_limit);
extern s32 FileSeek(s32 descriptor, s32 offset, s32 origin);

s32 card_seek_file_with_retries(s32 descriptor, s32 offset, s32 origin) {
    s32 i;
    /* The target's unoptimized local layout retains one unreferenced word. */
    s32 unused_local;
    s32 result;

    for (i = 0; i < 10; i++) {
        if (card_wait_for_operation_result(10) != 0)
            return -1;
        result = FileSeek(descriptor, offset, origin);
        if (result != -1)
            break;
    }
    return result;
}
