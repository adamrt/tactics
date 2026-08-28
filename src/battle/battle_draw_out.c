#include "psx/types.h"

extern s32 battle_draw_out_2(s32, s32);

s32 battle_draw_out(s32 arg0, s32 arg1) {
    return battle_draw_out_2(arg0, arg1 & 0xFF) & 0xFF;
}
