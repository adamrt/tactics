#include "psx/types.h"

extern void open_consume_all_card_events(void);
extern void open_set_card_slot(u8 slot);
extern s32 open_poll_card_info_until_stable(s32 retry_limit);

s32 open_check_memory_card_slots(void) {
    s32 found = 0;
    s32 result;

    open_consume_all_card_events();

    open_set_card_slot(1);
    result = open_poll_card_info_until_stable(3);
    if (result == 0 || result == 3) {
        found = 1;
    }

    open_set_card_slot(0);
    result = open_poll_card_info_until_stable(3);
    if (result == 0 || result == 3) {
        found = 1;
    }

    return found;
}
