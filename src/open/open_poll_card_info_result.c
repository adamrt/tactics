#include "psx/types.h"

extern u8 g_open_card_slot;
extern u8 g_open_card_info_pending;

extern s32 card_info(s32 port);
extern s32 card_status(s32 slot);
extern s32 open_poll_bios_card_event(void);
extern s32 open_card_info_with_retries(s32 port, s32 retry_limit);

s32 open_poll_card_info_result(void) {
    s32 status;
    s32 result;

    if (g_open_card_info_pending == 0) {
        card_info(g_open_card_slot << 4);
        g_open_card_info_pending = 1;
    }

    status = card_status(g_open_card_slot) & 1;
    result = open_poll_bios_card_event();
    if (status != 0 && result == -1) {
        g_open_card_info_pending = 0;
    }
    if (result >= 0) {
        g_open_card_info_pending = 0;
    }
    if (result > 0) {
        result = open_card_info_with_retries(g_open_card_slot << 4, 2);
    }
    if (result == 1) {
        result = 2;
    }
    return result;
}
