#include "psx/types.h"

extern s16 g_bunit_otag_index;
extern s16 g_bunit_semitrans_enabled;
extern s32 D_801EC8B8;
extern u8 g_bunit_otag_index_locked;
extern u8* (*g_bunit_render_command_handlers[])(void);

/* Twin of jobstts_run_render_command_stream; BUNIT's stream terminator is 0x1C. */
void bunit_run_render_command_stream(u8* data, s32 flags) {
    g_bunit_otag_index = 0;
    g_bunit_semitrans_enabled = 0;
    D_801EC8B8 = flags;
    g_bunit_otag_index_locked = 0;
    if (data[0] != 0x1C) {
        do {
            data = g_bunit_render_command_handlers[data[0]]();
        } while (data[0] != 0x1C);
    }
}
