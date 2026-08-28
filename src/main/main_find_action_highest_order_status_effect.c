#include "fft/status.h"
#include "psx/types.h"

/*
 * Return the highest-order status changed by an action. Bits 0-6 encode the
 * one-based status index, 0x80 marks removal, and 0x100 reflects flags_2 bit 3.
 */
s32 main_find_action_highest_order_status_effect(const u8* action) {
    s32 highest_order;
    s32 result;
    s32 status_index;
    s32 first_status_mask;
    const u8* order;
    /* Pins: as pseudos, status_offset is strength-reduced into the order
     * pointer (losing the `lui at / addu at,a3` form) and rounded_index moves
     * out of $v0 (losing the `move t3,v0` copy). Inline masks do not help. */
    register s32 status_offset __asm__("$7");
    register s32 rounded_index __asm__("$2");
    s32 byte_index;
    s32 status_mask;
    u8 current_order;
    s32 status_change;

    highest_order = -1;
    result = 0;
    status_index = 0;
    first_status_mask = 0x80;
    order = &g_status_effect_data[0].order;
    status_offset = 0;

    do {
        rounded_index = status_index;
        if (status_index < 0) {
            rounded_index = status_index + 7;
        }
        byte_index = rounded_index >> 3;
        rounded_index = first_status_mask >> (status_index & 7);
        __asm__("" : : "r"(rounded_index));
        status_change = (action + byte_index)[0x20] & rounded_index;
        status_mask = rounded_index;

        if (status_change != 0) {
            current_order = *order;
            if (current_order > highest_order) {
                highest_order = current_order;
                result = status_index + 0x81;
                if ((((const u8*)g_status_effect_data)[status_offset + 5] & 8) != 0) {
                    result = status_index + 0x181;
                }
            }
        }
        rounded_index = (s32)(action + byte_index);
        rounded_index = status_mask & ((const u8*)rounded_index)[0x1b];
        if (rounded_index != 0) {
            current_order = *order;
            if (current_order > highest_order) {
                highest_order = current_order;
                result = status_index + 1;
                if ((((const u8*)g_status_effect_data)[status_offset + 5] & 8) != 0) {
                    result = status_index + 0x101;
                }
            }
        }
        order += sizeof(status_effect_data_t);
        status_index++;
        status_offset += sizeof(status_effect_data_t);
    } while (status_index < 40);

    return result;
}
