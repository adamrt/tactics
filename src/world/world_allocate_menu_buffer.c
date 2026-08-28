#include "psx/types.h"

extern void* world_allocate_ui_buffer(s32 size);

void* world_allocate_menu_buffer(s32 size) {
    return world_allocate_ui_buffer(size);
}
