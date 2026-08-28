#include "psx/types.h"

typedef struct {
    u8 pad0[0x1C];
    s32 x1C;
    u8 pad20[0x22];
    s16 x42;
    u8 pad44[0x43];
    u8 x87;
    s32 x88;
    s32 x8C;
    s32 x90;
} HeightObj;

extern s32 battle_calculate_screen_z_from_misc_screen_data(HeightObj*);

void battle_something_height_related(HeightObj* o) {
    s32 step;
    s32 z;
    s32 v;

    step = o->x8C;
    z = o->x90;
    switch (o->x88) {
    case 0:
        z = battle_calculate_screen_z_from_misc_screen_data(o) << 12;
        step = (z - (o->x42 << 12)) / step;
        o->x88 = o->x88 + 1;
    case 1:
        if (o->x1C < z) {
            o->x1C = step + o->x1C;
        } else {
            o->x1C = z;
            o->x87 = 0;
        }
        v = o->x1C;
        o->x42 = v / 4096;
        break;
    }
    o->x8C = step;
    o->x90 = z;
}
