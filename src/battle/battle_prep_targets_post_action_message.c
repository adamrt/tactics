#include "psx/types.h"

extern void func_80072D8C(s32 x);
extern u8* battle_get_casting_unit_misc_data(void);
extern s32 battle_get_unit_misc_data_by_battle_id(u8 id);
extern s32 g_post_effect_msg_counter;

void battle_prep_targets_post_action_message(void) {
    u8* base;
    u8* p;
    s32 i;

    g_post_effect_msg_counter = 0;
    base = battle_get_casting_unit_misc_data();
    for (i = 0; i < base[0x18D]; i++) {
        p = base + i;
        func_80072D8C(battle_get_unit_misc_data_by_battle_id(p[0x18E]));
    }
}
