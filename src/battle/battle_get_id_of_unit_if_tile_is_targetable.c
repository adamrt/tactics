#include "psx/types.h"

extern s32 func_8017DCA8(s32 a0, s32 a1, s32 a2, s32 a3);

s32 battle_get_id_of_unit_if_tile_is_targetable(s32 a0, s32 a1, s32 a2) {
    return func_8017DCA8(a0, a1, a2, 0);
}
