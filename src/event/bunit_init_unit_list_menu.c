#include "psx/types.h"

typedef void (*BunitFn)();

extern void bunit_init_scrollable_list_menu_core(s32, s32, s32);
extern void bunit_set_event_speed(s32);
extern s32 func_801C41E0(s32);
extern void bunit_init_rhombus_cursor_tpages(void);

extern void bunit_get_unit_s16_0c_12_or_18();
extern void func_801C4164();
extern void bunit_get_unit_s16_00();
extern void bunit_get_unit_s16_08();
extern void bunit_get_unit_s16_26();
extern void bunit_get_unit_s16_28();

extern BunitFn g_bunit_row_callbacks;
extern BunitFn g_bunit_row_callback_1;
extern BunitFn g_bunit_row_callback_4;
extern BunitFn g_bunit_row_callback_5;
extern BunitFn g_bunit_row_callback_6;
extern BunitFn g_bunit_row_callback_7;
extern s8 g_bunit_unit_list_page_offset;
extern u8 D_801CF508;
extern u8 D_801CF509;
extern s32 D_801CF4BC;

void bunit_init_unit_list_menu(void) {
    s32 ret;

    bunit_init_scrollable_list_menu_core(0, 0, 0);
    g_bunit_row_callbacks = bunit_get_unit_s16_0c_12_or_18;
    g_bunit_row_callback_1 = func_801C4164;
    g_bunit_row_callback_4 = bunit_get_unit_s16_00;
    g_bunit_row_callback_5 = bunit_get_unit_s16_08;
    g_bunit_row_callback_6 = bunit_get_unit_s16_26;
    g_bunit_row_callback_7 = bunit_get_unit_s16_28;
    bunit_set_event_speed(0);
    ret = func_801C41E0(g_bunit_unit_list_page_offset);
    D_801CF508 = ret;
    D_801CF509 = ret;
    if (D_801CF508 != 0) {
        D_801CF4BC = 0x90;
    } else {
        D_801CF4BC = 0;
    }
    bunit_init_rhombus_cursor_tpages();
}
