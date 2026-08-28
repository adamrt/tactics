#include "fft/jobstts.h"

extern volatile jobstts_ability_selection_state_t g_jobstts_ability_selection_states[];

void jobstts_store_ability_selection_state(s32 index, s32 selected_index,
    s32 scroll_index,
    const u16* abilities) {
    g_jobstts_ability_selection_states[index].selected_index = selected_index;
    g_jobstts_ability_selection_states[index].scroll_index = scroll_index;
    g_jobstts_ability_selection_states[index].selected_ability_id = abilities[selected_index] & 0x3ff;
}
