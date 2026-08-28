#include "psx/types.h"

extern u8 g_bunit_reorder_list_initialized;
extern s16 g_bunit_reorder_list_index;
extern s16 g_bunit_reorder_list_entries[];
extern s16 g_bunit_reorder_menu_result;
extern u8 D_801CF458[];
extern u8 D_801EB158[];
extern s32 D_801CF454;
extern u8 D_801CF904[];
extern s32 g_bunit_selection_text_id;
extern s16 D_801CF900;

extern void bunit_out_001c70c4_001c7100(s32 a, s16* b);
extern void bunit_out_001cb944_001cba38(u8* a, u8* b, s16* c, s32 d);
extern s32 bunit_run_menu_descriptor_thread(s32 a, u8* b);
extern void bunit_reset_menu_results(void);
extern void bunit_out_001c7104_001c7144(s32 a, s16* b);
extern void bunit_out_001c6f48_001c70c0(s32 a);
extern void bunit_out_001c6330_001c63a4(void);
extern void bunit_out_001c6274_001c632c(void);

void bunit_run_reorder_list_menu(void) {
    s16 opts[16];
    s16* src;
    s16* dst;
    s32 i;
    s16 r;
    s32 sel;
    s32 keep;

    if (g_bunit_reorder_list_initialized == 0) {
        g_bunit_reorder_list_index = 0;
        bunit_out_001c70c4_001c7100(1, g_bunit_reorder_list_entries);
        i = 0;
        src = g_bunit_reorder_list_entries;
        dst = opts;
        do {
            *dst = *src + 1;
            src++;
            i++;
            dst++;
        } while (i < 11);
        opts[11] = -1;
        bunit_out_001cb944_001cba38(D_801CF458, D_801EB158, opts, 1);
        g_bunit_reorder_list_initialized = 1;
    }

    if (bunit_run_menu_descriptor_thread(0xF, D_801CF904) == 0) {
        g_bunit_reorder_list_initialized = 0;
        D_801CF454 = -1;
    }

    g_bunit_selection_text_id = g_bunit_reorder_list_entries[g_bunit_reorder_list_index] + 0x1002;
    r = g_bunit_reorder_menu_result;
    if (r != -1) {
        sel = r;
        keep = g_bunit_reorder_list_entries[sel];
        for (sel--; sel >= 0; sel--) {
            g_bunit_reorder_list_entries[sel + 1] = g_bunit_reorder_list_entries[sel];
        }
        g_bunit_reorder_list_entries[0] = keep;
        bunit_reset_menu_results();
        i = 0;
        src = g_bunit_reorder_list_entries;
        dst = opts;
        do {
            *dst = *src + 1;
            src++;
            i++;
            dst++;
        } while (i < 11);
        opts[11] = -1;
        bunit_out_001cb944_001cba38(D_801CF458, D_801EB158, opts, 1);
        D_801CF900 = 1;
        bunit_out_001c7104_001c7144(1, g_bunit_reorder_list_entries);
        bunit_out_001c6f48_001c70c0(1);
        bunit_out_001c6330_001c63a4();
        bunit_out_001c6274_001c632c();
    }
}
