#include "psx/types.h"

typedef struct OpenScriptDispatchState {
    u32 flags;
    u8 pad_04[0x1c];
    s32 external_counter;
    u8 pad_24[8];
    s32 offset;
} OpenScriptDispatchState;

extern OpenScriptDispatchState g_open_script_dispatch_state;

void open_parse_wait_for_external_counter(s16* entry) {
    u32 flags;
    s32 counter;
    s32 limit;
    s32 offset;
    OpenScriptDispatchState* state;

    state = &g_open_script_dispatch_state;
    flags = state->flags;
    entry++;
    if (flags & 4) {
        limit = *entry;
        counter = state->external_counter;
        if (counter >= limit) {
            offset = state->offset;
            state->flags = flags ^ 4;
            state->offset = offset + 4;
        } else {
            state->flags = flags ^ 2;
        }
    } else {
        state->flags = (flags | 4) ^ 2;
        state->external_counter = 0;
    }
}
