#include "psx/types.h"

extern s32 card_create_new(s32 port);
extern s32 card_wait_for_hardware_event_result(void);
extern s32 card_wait_for_operation_result(s32 retry_limit);

s32 card_create_new_with_retries(s32 port, s32 retry_limit) {
    s32 i;
    s32 result;

    for (i = 0; i < retry_limit; i++) {
        if (card_create_new(port) == 1) {
            result = card_wait_for_hardware_event_result();
            if (result >= 3)
                result = 1;
            if (result == 0)
                break;
            if (card_wait_for_operation_result(1) == 0) {
                result = 0;
                break;
            }
        } else {
            result = 2;
        }
    }
    return result;
}
