#include "psx/types.h"

extern s16 g_bunit_indexed_values[];
extern u8 g_bunit_menu_state;

s16 bunit_update_wrapped_horizontal_selection(
    u16 entry_count, u8 selection_index, s32 input_mask);

/* Update a wrapped selection and request the supplied menu state on change. */
void bunit_update_horizontal_selection_and_mark_change(
    u16 entry_count, u8 selection_index, s32 input_mask, u8 changed_state) {
    s16 previous_selection;
    s16 selection;

    selection_index &= 0xff;
    previous_selection = g_bunit_indexed_values[selection_index];
    selection = bunit_update_wrapped_horizontal_selection(
        entry_count, selection_index, input_mask);
    if (previous_selection != selection) {
        g_bunit_menu_state = changed_state;
    }
}
