#include "psx/types.h"

extern void func_800898A0(void* unit, s32 allow_height_change);

void battle_accelerate_unit_to_destination_no_height_change(void* unit) {
    func_800898A0(unit, 0);
}
