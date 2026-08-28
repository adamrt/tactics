#include "psx/types.h"

extern s32 (*g_call_inner_subroutine_target)();
extern s32 main_load_data_from_disc(s32 lba, s32 size, void* destination);
extern s32 main_check_file_still_loading(void);
extern s32 call_inner_subroutine();
extern void switch_to_next_event_thread(void);

void attack_out_enqueue_open_file(s32 lba, s32 size, void* destination) {
    while (1) {
        g_call_inner_subroutine_target = main_load_data_from_disc;
        if (call_inner_subroutine(lba, size, destination) == 0) {
            break;
        }
        switch_to_next_event_thread();
    }
    while (1) {
        g_call_inner_subroutine_target = main_check_file_still_loading;
        if (call_inner_subroutine() == 0) {
            break;
        }
        switch_to_next_event_thread();
    }
}
