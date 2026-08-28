#ifndef FFT_JOBSTTS_H
#define FFT_JOBSTTS_H

#include "psx/types.h"

typedef struct jobstts_ability_selection_state {
    s16 selected_index;
    s16 scroll_index;
    u16 selected_ability_id;
} jobstts_ability_selection_state_t;

typedef char assert_jobstts_ability_selection_state_size[sizeof(jobstts_ability_selection_state_t) == 6 ? 1 : -1];

#endif
