#include "psx/types.h"

extern u16 battle_load_halfword(u8* p);
extern s32 func_80147928(u16* id, s32* flag);
extern s32 func_801479AC(u16* id, s32* i, s32* flag);
extern void battle_unset_misc_data_move_flag_bit_1(s32 id);
extern void battle_flip_misc_data_move_flag_bit_1(s32 id);
extern void battle_set_specific_unit_animation_value_when_battle_init(s32 id, s32 value);
extern void func_8013E874(void);

void battle_unit_anim(u8* arg) {
    u16 id;
    s32 flag;
    s32 i;
    s32 anim;
    s32 t;

    id = battle_load_halfword(arg);
    if (func_80147928(&id, &flag) == 0) {
        return;
    }
    i = 0;
    do {
        if (func_801479AC(&id, &i, &flag) != 0) {
            t = arg[4];
            if (t == 0) {
                battle_unset_misc_data_move_flag_bit_1(id);
            } else if (t == 1) {
                battle_flip_misc_data_move_flag_bit_1(id);
            }
            anim = (s16)battle_load_halfword(arg + 2);
            battle_set_specific_unit_animation_value_when_battle_init(id, anim);
            if ((u32)(anim - 0x53) < 3) {
                func_8013E874();
            }
            if (flag == 0) {
                return;
            }
        }
        i = i + 1;
    } while (i < 0x15);
}
