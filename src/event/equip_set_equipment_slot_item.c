#include "psx/types.h"

extern s16* g_equip_unit_data[];

extern void equip_adjust_item_inventory_count(s16, s32);
extern s32 func_801C83D0(s16, s16, s16);
extern void func_801C6DB4(void);

s32 equip_set_equipment_slot_item(s16 arg0, s16 arg1, s32 arg2) {
    s16 value;
    s32 ret;

    value = arg2 & 0x3FF;
    ret = func_801C83D0(arg0, arg1, value);
    if (ret < 0) {
        return ret;
    }
    if (arg0 != 1) {
        equip_adjust_item_inventory_count(g_equip_unit_data[arg0][arg1 + 42], 1);
    }
    if (arg1 < 2 && ret != 1) {
        s32 other = (arg1 == 0);
        if (arg0 != 1) {
            equip_adjust_item_inventory_count(g_equip_unit_data[arg0][other + 42], 1);
        }
        g_equip_unit_data[arg0][other + 42] = 0;
    }
    g_equip_unit_data[arg0][arg1 + 42] = value;
    if (arg0 != 1) {
        func_801C6DB4();
    }
    return 1;
}
