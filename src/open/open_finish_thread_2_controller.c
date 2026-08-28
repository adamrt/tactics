#include "fft/opening.h"

/* The thread-2 controller's view of its open_controller_record_t. */
typedef struct OpenThreadCompletion {
    s32 run_followup;
    s32 result;
} OpenThreadCompletion;

extern s32 g_open_formation_entry_mask;

s32 world_check_thread_running_status(s32 thread_index);
void func_800e86ec(void);

void open_finish_thread_2_controller(OpenThreadCompletion* completion) {
    if (world_check_thread_running_status(2) == 0) {
        g_open_formation_entry_mask = completion->result;
        g_open_current_controller_index--;
        if (completion->run_followup != 0) {
            func_800e86ec();
        }
    }
}
