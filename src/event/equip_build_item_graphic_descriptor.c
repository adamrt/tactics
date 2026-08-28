#include "psx/types.h"

typedef struct {
    u8 pad[12];
    u8 c;
    u8 d;
    u16 e;
    u8 tail[8];
} S001C3B98;

extern void func_80136B10(S001C3B98*);
extern s16 func_8002398C(s32, s32, s32, s32);

void equip_build_item_graphic_descriptor(s16* arg0) {
    S001C3B98 sp10;

    func_80136B10(&sp10);
    arg0[0] = sp10.c;
    arg0[1] = sp10.d;
    arg0[2] = 0x10;
    arg0[3] = 0x10;
    arg0[4] = sp10.e;
    arg0[5] = func_8002398C(0, 0, 0x380, 0x120);
}
