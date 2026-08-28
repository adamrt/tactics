#include "psx/types.h"

extern s32 g_card_thread_state;
extern void card_set_thread_completion_parameters(s32 id);

void card_finish_thread_and_clear_state(s32 id) {
    card_set_thread_completion_parameters(id);
    g_card_thread_state = 0;
}
