#include "psx/types.h"

extern u8* g_world_menu_scripts[];

/* Fetch one of the nine menu-script streams by index. */
u8* world_get_menu_script(s32 index) {
    return g_world_menu_scripts[index];
}
