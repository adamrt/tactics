#include "psx/types.h"

typedef struct {
    u8 pad_0[0x24];
    u8 field_24;
    u8 pad_25[0x22];
    u8 field_47;
    u16 field_48;
    u8 pad_end[0x24];
} SomeStruct;

typedef struct {
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
} ItemInfo;

typedef struct {
    s32 field_0;
    u8 field_4;
} RareBuf;

extern ItemInfo* func_801802C8(u8 a, u8 b, u32 c);
extern s32 main_pass_fail_roll(s32 a, s32 b);
extern s32 battle_get_script_variable(s32 var_id);
extern void battle_move_find_item_flag_calculation(s32 a, u8 b, s32 c);
extern RareBuf D_8018F8A0;

void* battle_rare_common_item_determination(SomeStruct* arg0) {
    ItemInfo* info;
    u8 val;

    info = func_801802C8(arg0->field_47, (u8)arg0->field_48, (u32)arg0->field_48 >> 15);
    if (main_pass_fail_roll(0x64, 0x64 - arg0->field_24) == 0) {
        val = info->field_2;
    } else {
        val = info->field_3;
    }
    D_8018F8A0.field_4 = val;
    battle_move_find_item_flag_calculation(battle_get_script_variable(0x33), info->field_1, 1);
    D_8018F8A0.field_0 = 0;
    return &D_8018F8A0;
}
