#include "psx/types.h"

extern s32 open_poll_card_info_result(void);

s32 open_poll_card_info_until_stable(s32 retry_limit) {
    s32 attempts = 0;
    s32 consecutive_successes = 0;
    s32 result;

    while (attempts < retry_limit) {
        do {
            result = open_poll_card_info_result();
        } while (result == -1);

        if (result == 0) {
            consecutive_successes++;
            attempts--;
            if (consecutive_successes == 3) {
                break;
            }
        } else {
            consecutive_successes = 0;
        }
        attempts++;
    }
    return result;
}
