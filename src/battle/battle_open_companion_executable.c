#include "psx/types.h"

extern s32 call_inner_subroutine();
extern void main_load_data_from_disc(void);
extern void main_check_file_still_loading(void);
extern void (*g_call_inner_subroutine_target)(void);
extern s32 g_event_overlay_load_address;
extern s32 g_companion_executable_request_index;
extern s32 g_companion_executable_loading;
extern s32 D_80168EF8[];
extern s32 D_80168F38[];
extern s32 D_80168F78[];

void battle_open_companion_executable(void) {
    s32 idx;

    idx = g_companion_executable_request_index;
    if ((idx != 0) && (g_companion_executable_loading == 0)) {
        g_call_inner_subroutine_target = main_load_data_from_disc;
        if (call_inner_subroutine(D_80168EF8[idx], D_80168F38[idx],
                D_80168F78[idx] + g_event_overlay_load_address)
            == 0) {
            g_companion_executable_loading = 1;
        }
    } else if ((g_companion_executable_request_index != 0) && (g_companion_executable_loading != 0)) {
        g_call_inner_subroutine_target = main_check_file_still_loading;
        if (call_inner_subroutine() == 0) {
            g_companion_executable_loading = 0;
            g_companion_executable_request_index = 0;
        }
    }
}
