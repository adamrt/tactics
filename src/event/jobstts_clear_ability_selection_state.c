#include "fft/jobstts.h"

extern void* memset(void* destination, s32 value, u32 size);
extern jobstts_ability_selection_state_t g_jobstts_ability_selection_states[];

void jobstts_clear_ability_selection_state(s32 index) {
    memset(&g_jobstts_ability_selection_states[index], 0,
        sizeof(jobstts_ability_selection_state_t));
}
