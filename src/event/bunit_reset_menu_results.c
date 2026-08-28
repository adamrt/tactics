#include "psx/types.h"

extern s16 g_bunit_primary_menu_result;
extern s16 g_bunit_reorder_menu_result;

void bunit_reset_menu_results(void) {
    g_bunit_primary_menu_result = -1;
    g_bunit_reorder_menu_result = -1;
}
