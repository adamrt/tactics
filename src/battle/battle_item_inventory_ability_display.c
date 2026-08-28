#include "psx/types.h"

extern s32 func_80181B94(s32, s32);

s32 battle_item_inventory_ability_display(s32 arg0, s32 arg1) {
    return func_80181B94(arg0, arg1 & 0xFF) & 0xFF;
}
