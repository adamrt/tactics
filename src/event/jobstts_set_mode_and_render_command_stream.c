#include "psx/types.h"

extern void func_801e4338(s32 event_mode);
extern void jobstts_run_render_command_stream(void* first, void* second);

void jobstts_set_mode_and_render_command_stream(void* first, void* second,
    s32 event_mode) {
    func_801e4338(event_mode);
    jobstts_run_render_command_stream(first, second);
}
