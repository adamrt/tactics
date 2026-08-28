#include "psx/types.h"

extern s32 main_read_controller_input(s32 port);

s32 world_read_controller_input(void) {
    return main_read_controller_input(0);
}
