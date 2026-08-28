#include "psx/types.h"

extern s32 card_poll_operation_result(void);

s32 card_wait_for_operation_result(s32 retry_limit) {
    s32 result;
    s32 i = 0;

    while (i < retry_limit) {
        do {
            result = card_poll_operation_result();
        } while (result == -1);
        if (result == 0)
            break;
        i++;
    }
    return result;
}
