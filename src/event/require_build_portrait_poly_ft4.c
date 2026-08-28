#include "psx/types.h"

extern void build_unit_battle_portrait_poly(void* output, s32 flags);
extern void require_set_formation_icon_uv(void* output, s32 id);

void require_build_portrait_poly_ft4(s32 flags, void* output) {
    if ((flags & 0x300) == 0) {
        build_unit_battle_portrait_poly(output, flags);
    }
    if ((flags & 0x100) != 0) {
        require_set_formation_icon_uv(output, flags & 0xff);
    }
}
