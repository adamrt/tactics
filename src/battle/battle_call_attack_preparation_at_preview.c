#include "psx/types.h"

extern s32 func_8017C45C(u8* arg, s32 addr, s32 flag);
extern void battle_enable_disable_acting_status(s32);
extern s32 g_battle_action_type;
extern u8 battle_stats[];

s32 battle_call_attack_preparation_at_preview(u8* arg) {
    s32 s;
    s32 r;

    s = (s32)&battle_stats[*arg * 0x1C0];
    r = func_8017C45C(arg, s + 0x16E, 1);
    if (r == 1 && g_battle_action_type == 0) {
        battle_enable_disable_acting_status(s);
    }
    return r;
}
