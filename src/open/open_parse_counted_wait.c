#include "psx/types.h"

typedef struct OpenScriptDispatchState {
    u32 flags;
    u8 pad_04[0x20];
    s32 wait_counter;
    u8 pad_28[4];
    s32 offset;
} OpenScriptDispatchState;

extern OpenScriptDispatchState g_open_script_dispatch_state;

void open_parse_counted_wait(s16* entry) {
    u32 flags;
    s32 counter;
    s32 offset;
    OpenScriptDispatchState* state;

    state = &g_open_script_dispatch_state;
    flags = state->flags;
    entry++;
    if (flags & 4) {
        counter = state->wait_counter + 1;
        state->wait_counter = counter;
        if (counter >= *entry) {
            offset = state->offset;
            state->flags = flags ^ 4;
            state->offset = offset + 4;
        } else {
            state->flags = flags ^ 2;
        }
    } else {
        state->flags = (flags | 4) ^ 2;
        state->wait_counter = 0;
    }
}
