#include "psx/types.h"

extern s32 func_8002398C(s32, u8, s32, s32);
extern void func_801CA72C(s32, s32, s32, s32, s32);
extern s16 g_equip_sprite_ot_index;

u8* equip_submit_sprite_prim_from_stream(u8* arg0) {
    s32 tmp = func_8002398C(0, arg0[2], 0x100, 0);
    func_801CA72C(0, 0, tmp & 0xFFFF, 0, g_equip_sprite_ot_index);
    return arg0 + arg0[1];
}
