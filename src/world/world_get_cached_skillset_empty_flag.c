#include "psx/types.h"

extern s32 g_world_cached_skillset_empty;

s32 world_get_cached_skillset_empty_flag(void) {
    return g_world_cached_skillset_empty;
}
