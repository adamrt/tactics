#include "psx/types.h"

extern s8 g_bunit_unit_list_scroll_step;
extern s8 g_bunit_unit_list_page_offset;
extern s16 g_bunit_selected_unit_index;

s32 bunit_unit_list_needs_scroll(void) {
    s32 ret = 0;

    if (g_bunit_unit_list_scroll_step == 0) {
        switch (g_bunit_unit_list_page_offset) {
        case -0x78:
            if (g_bunit_selected_unit_index < 8) {
                ret = 1;
            }
            break;
        case -0x3C:
            if (g_bunit_selected_unit_index >= 0x10) {
                ret = 1;
            } else if (g_bunit_selected_unit_index < 4) {
                ret = 1;
            }
            break;
        case 0:
            if (g_bunit_selected_unit_index >= 0xC) {
                ret = 1;
            }
            break;
        }
    } else {
        ret = 1;
    }
    return ret;
}
