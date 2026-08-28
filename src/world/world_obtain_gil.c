#include "psx/types.h"

extern s32 world_get_script_variable(s32 id);
extern void world_set_script_variable(s32 id, s32 value);

s32 world_obtain_gil(s32 delta) {
    s32 gil;

    gil = world_get_script_variable(0x2C) + delta;
    if (gil < 0) {
        gil = 0;
    }
    if (gil > 0x5F5E0FF) {
        gil = 0x5F5E0FF;
    }
    world_set_script_variable(0x2C, gil);
    return gil;
}
