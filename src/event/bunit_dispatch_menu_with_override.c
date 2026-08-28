#include "psx/types.h"

extern void func_801CB058(s32 arg0);
extern void bunit_run_render_command_stream(s32 arg0, s32 arg1);

/* BUNIT.OUT 001c85f8 - Invoke menu action `menu_id`+`state`, but clear `state` to
 * 0 whenever the override flag is set (also passed to func_801CB058). */
void bunit_dispatch_menu_with_override(s32 menu_id, s32 state, s32 override) {
    s32 effective_state = state;
    if (override != 0) {
        effective_state = 0;
    }
    func_801CB058(override);
    bunit_run_render_command_stream(menu_id, effective_state);
}
