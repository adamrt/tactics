#include "psx/types.h"

extern s16 world_load_halfword(const u8* source);
extern s32 world_get_script_variable(s32 variable_id);
extern void world_switch_to_next_thread(void);

void world_wait_for_script_value(const u8* parameters) {
    s32 variable_id = world_load_halfword(parameters);
    s16 test_value = world_load_halfword(parameters + 2);

    do {
        if (world_get_script_variable(variable_id) >= test_value) {
            break;
        }
        world_switch_to_next_thread();
    } while (1);
}
