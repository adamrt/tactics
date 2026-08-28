#include "psx/types.h"

extern u16 g_open_transition_flags;
extern s16 g_open_transition_mode;
extern s16 g_open_transition_current_index;
extern s16 g_open_transition_target_index;
extern s16 g_open_transition_intensity;
extern s32 g_open_transition_entry_table;

void open_initialize_transition_request(s32 target, s32 mode, s32 data) {
    g_open_transition_flags = 1;
    g_open_transition_current_index = 0;
    g_open_transition_target_index = target;
    g_open_transition_entry_table = data;
    g_open_transition_mode = mode;
    g_open_transition_intensity = 0x80;
}
