#include "psx/types.h"

extern s32 (*g_call_inner_subroutine_target)();
extern s32 call_inner_subroutine();
extern void switch_to_next_event_thread(void);
extern s32 main_call_build_file_header(s32 lba, s32 size, void* destination);
extern s32 main_check_file_still_loading(void);

void require_load_file_sync(s32 lba, s32 size, void* destination) {
    do {
        g_call_inner_subroutine_target = main_call_build_file_header;
        if (call_inner_subroutine(lba, size, destination) == 0) {
            break;
        }
        switch_to_next_event_thread();
    } while (1);

    do {
        g_call_inner_subroutine_target = main_check_file_still_loading;
        if (call_inner_subroutine() == 0) {
            break;
        }
        switch_to_next_event_thread();
    } while (1);
}
