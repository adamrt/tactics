#include "psx/types.h"

typedef void (*OpenScriptEntryHandler)(s16* entry);

typedef struct OpenScriptDispatchState {
    u32 flags;
    u8 pad_04[0x24];
    void* base;
    s32 offset;
} OpenScriptDispatchState;

extern OpenScriptDispatchState g_open_script_dispatch_state;
extern OpenScriptEntryHandler g_open_script_entry_handlers[];

void open_update_script_timing_and_record_values(void);
void func_8006f228(void);
void open_update_opntex_sequence(void);
void func_8006f5d4(void);
s16* open_add_pointer_offset(void* base, s32 offset);

s32 open_initialize_and_dispatch_script_entries(void) {
    OpenScriptDispatchState* state;
    void** dispatch_arguments;
    OpenScriptEntryHandler* handlers;
    s32 result;
    s16* entry;
    u32 flags;

    open_update_script_timing_and_record_values();
    func_8006f228();
    open_update_opntex_sequence();
    func_8006f5d4();

    state = &g_open_script_dispatch_state;
    result = state->flags | 2;
    state->flags = result;
    result &= 2;
    if (result == 0) {
        result = 1;
        goto done;
    }
    dispatch_arguments = &state->base;
    handlers = g_open_script_entry_handlers;

dispatch_entry:
    entry = open_add_pointer_offset(dispatch_arguments[0],
        *(s32*)&dispatch_arguments[1]);
    handlers[*entry](entry);
    flags = *(u32*)((u8*)dispatch_arguments - 0x28);
    /* Tested as anonymous temporaries: testing `result` itself lets cse
     * delete the explicit `result = 0` on the fall-through. */
    if ((flags & 1) == 0) {
        result = 0;
        goto done;
    }
    if ((flags & 2) != 0) {
        goto dispatch_entry;
    }
    result = 1;

done:
    return result;
}
