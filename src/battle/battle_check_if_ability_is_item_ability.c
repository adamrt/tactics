#include "psx/types.h"

extern s16 D_801B63F0[];

s32 battle_check_if_ability_is_item_ability(s32 ability_id) {
    s32 v;
    v = D_801B63F0[ability_id];
    if (v < 0) {
        v = ~v;
    }
    return (v & 0x800) > 0;
}
