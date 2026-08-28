#include "psx/etc.h"
#include "psx/types.h"

extern s32 card_load(s32 port);
extern s32 card_wait_for_bios_event_result(void);

s32 card_load_with_retries(s32 port, s32 retry_limit) {
    s32 i;
    s32 result;

    for (i = 0; i < retry_limit; i++) {
        if (card_load(port) == 1) {
            result = card_wait_for_bios_event_result();
            if (result == 0)
                break;
        } else {
            result = 2;
        }
        VSync(2);
    }
    return result;
}
