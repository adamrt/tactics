#include "psx/types.h"

extern u8 g_card_selected_slot;
extern u8 g_card_operation_pending;

extern s32 card_info(s32 port);
extern s32 card_status(s32 slot);
extern s32 card_poll_bios_event_result(void);
extern s32 card_info_with_retries(s32 port, s32 retry_limit);

s32 card_poll_operation_result(void) {
    s32 status;
    s32 result;

    if (g_card_operation_pending == 0) {
        card_info(g_card_selected_slot << 4);
        g_card_operation_pending = 1;
    }

    status = card_status(g_card_selected_slot) & 1;
    result = card_poll_bios_event_result();
    if (status != 0 && result == -1) {
        result = 2;
    }
    if (result >= 0) {
        g_card_operation_pending = 0;
    }
    if (result > 0) {
        result = card_info_with_retries(g_card_selected_slot << 4, 2);
    }
    if (result == 1) {
        result = 2;
    }
    return result;
}
