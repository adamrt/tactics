#include "fft/map.h"

extern s32 g_map_gns_record_cursor;

extern s32 battle_get_script_variable(s16 script_variable_id);
extern s32 battle_gns_record_matches_map_state(u8 comparison, s16 record_state,
    s16 requested_state);
extern void dispatch_map_gns_resource(s32 resource_type, gns_file_record_t* record);

s32 battle_process_map_gns_record(s32 phase, gns_file_record_t* record) {
    char unused_zeroes[8] = { 0 };
    s32 unused_sizes[4] = { 0x1000, 0x1000, 0x1000, 0 };
    s32 resource_type;
    /* Pin: the last resource-type test compares against a 0x8b in $v0 while
     * a second 0x8b for resource_type sits in $a0 in the branch delay slot.
     * Unpinned, GCC CSEs the two constants into $a0 (either assignment
     * order) and leaves the delay slot empty. */
    register s32 comparison_type __asm__("$2");
    s32 requested_layout;
    s32 requested_layout_and_weather;
    gns_file_record_t* selected;

    if (phase == 2) {
        /* Everything below works on this copy; the parameter itself dies
         * here, which keeps it out of a callee-saved register. */
        selected = record;
        if (selected->resource_type == GNS_RESOURCE_SET_INDOOR) {
            resource_type = GNS_RESOURCE_SET_INDOOR;
            goto dispatch;
        } else if (selected->resource_type == GNS_RESOURCE_SET_OUTDOOR) {
            resource_type = GNS_RESOURCE_SET_OUTDOOR;
            goto dispatch;
        } else if (selected->resource_type == GNS_RESOURCE_CLEAR_SNOW) {
            resource_type = GNS_RESOURCE_CLEAR_SNOW;
            goto dispatch;
        } else if (selected->resource_type == GNS_RESOURCE_SET_SNOW) {
            resource_type = GNS_RESOURCE_SET_SNOW;
            goto dispatch;
        } else if (selected->resource_type == GNS_RESOURCE_RESERVED_8A) {
            resource_type = GNS_RESOURCE_RESERVED_8A;
            goto dispatch;
        }
        comparison_type = GNS_RESOURCE_SET_WEATHER_MODIFIER;
        resource_type = GNS_RESOURCE_SET_WEATHER_MODIFIER;
        if (selected->resource_type == comparison_type) {
            goto dispatch;
        }

        /*
         * Requested map state, packed like gns_file_record_t.map_state: layout in
         * bits 0-11, weather in 12-14, time of day in 15.  The target reads
         * the record's variable id and map state as single bytes (lbu), not
         * as the halfwords the struct declares, so those two stay byte reads.
         */
        requested_layout = battle_get_script_variable(((u8*)selected)[0]) & 0xfff;
        requested_layout_and_weather = requested_layout | ((battle_get_script_variable(0x23) & 7) << 12);
        if ((battle_gns_record_matches_map_state(
                 selected->map_state_comparison, ((u8*)selected)[2],
                 requested_layout_and_weather | ((battle_get_script_variable(0x24) & 1) << 15))
                << 16)
            != 0) {
            resource_type = selected->resource_type;
            goto dispatch;
        }
        goto advance;
    dispatch:
        dispatch_map_gns_resource(resource_type, selected);
    advance:
        /* Byte read of start_sector's low byte, as the target does. */
        g_map_gns_record_cursor += ((u8*)selected)[8];
    }
    return 0;
}
