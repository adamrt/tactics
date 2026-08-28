#include "psx/types.h"

extern s8 g_bunit_job_menu_active;
extern s8 g_bunit_job_menu_phase;
extern u8 g_bunit_menu_state;
extern s32 D_801CF454;
extern void bunit_set_indexed_s16(s32 index, s32 value);
extern void func_801C657C(void);
extern s32 bunit_run_job_list_menu(void);
extern s32 func_801CCF74(void);
extern void bunit_reset_menu_input_masks(void);

void bunit_update_job_menu(void) {
    if (g_bunit_job_menu_active == 0) {
        g_bunit_job_menu_active = 1;
        g_bunit_job_menu_phase = 0;
        bunit_set_indexed_s16(0, 0);
        func_801C657C();
        g_bunit_menu_state = 1;
    }
    if (g_bunit_job_menu_phase == 0) {
        g_bunit_job_menu_phase = bunit_run_job_list_menu();
    } else if (g_bunit_job_menu_phase == 1) {
        g_bunit_job_menu_phase = func_801CCF74();
    }
    if (g_bunit_job_menu_phase == -1) {
        D_801CF454 = -1;
        bunit_reset_menu_input_masks();
        g_bunit_job_menu_active = 0;
    }
}
