#include "psx/types.h"

extern s8 g_jobstts_otag_index_locked;
extern s16 g_jobstts_otag_index;
extern s16 g_jobstts_semitransparency;
extern s32 D_801FA6C8;
extern u8* (*g_jobstts_render_command_handlers[])(u8*);
extern s8 g_jobstts_transition_frame;

void jobstts_run_render_command_stream(u8* data, s32 flags) {
    g_jobstts_otag_index_locked = 0;
    g_jobstts_otag_index = 0;
    g_jobstts_semitransparency = 0;
    D_801FA6C8 = flags;
    while (*data != 0x16) {
        data = g_jobstts_render_command_handlers[*data](data);
    }
    if (g_jobstts_transition_frame < 10) {
        g_jobstts_transition_frame = g_jobstts_transition_frame + 1;
    }
}
