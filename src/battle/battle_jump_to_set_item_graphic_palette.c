#include "psx/types.h"

extern void func_80083758(s32 arg0, s32 arg1);
extern s32 battle_get_unit_misc_data_by_battle_id(s32 id);

void battle_jump_to_set_item_graphic_palette(s32 arg0, u16 arg1) {
    func_80083758(arg0, battle_get_unit_misc_data_by_battle_id(arg1));
}
