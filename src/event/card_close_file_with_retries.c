#include "psx/types.h"

extern s32 g_card_open_descriptor;
extern s32 card_wait_for_operation_result(s32 retry_limit);
extern s32 FileClose(s32 descriptor);

s32 card_close_file_with_retries(s32 descriptor) {
    s32 i;
    s32 wait_success;
    s32 close_result;

    for (i = 0; i < 10; i++) {
        wait_success = card_wait_for_operation_result(10) == 0;
        close_result = FileClose(descriptor);
        if (close_result == descriptor) {
            break;
        } else {
            wait_success = 0;
        }
    }
    g_card_open_descriptor = -1;
    return wait_success;
}
