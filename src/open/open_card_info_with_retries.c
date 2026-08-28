#include "psx/types.h"

extern s32 card_info(s32 port);
extern s32 open_wait_for_bios_card_event(void);

s32 open_card_info_with_retries(s32 port, s32 retry_limit) {
    s32 i;
    s32 result;

    for (i = 0; i < retry_limit; i++) {
        if (card_info(port) == 1) {
            result = open_wait_for_bios_card_event();
            if (result == 0)
                break;
        } else {
            result = 1;
        }
    }
    return result;
}
