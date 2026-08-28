#include "psx/types.h"

extern u8 g_card_selected_slot;
extern s32 card_load_with_retries(s32 port, s32 retry_limit);
extern s32 card_create_new_with_retries(s32 port, s32 retry_limit);
extern s32 card_wait_for_operation_result(s32 retry_limit);

s32 card_open_or_create_selected_card(void) {
    s32 result = card_wait_for_operation_result(10);

    if (result == 3) {
        result = card_create_new_with_retries(g_card_selected_slot << 4, 10);
        if (result != 0)
            return 2;
    }
    if (result == 0)
        result = card_load_with_retries(g_card_selected_slot << 4, 30);
    if (result == 3)
        return 3;
    if (result != 0)
        result = 2;
    return result;
}
