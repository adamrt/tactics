#include "psx/types.h"

extern u16 D_801531C4;
extern s32* g_world_event_words;

void world_clear_current_event_word_bit_0(void) {
    s32* word = &g_world_event_words[D_801531C4];
    *word &= ~1;
}
