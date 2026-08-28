#include "psx/types.h"

typedef struct {
    s32 value;
    s32 extra;
} WldcoreSlot;

extern WldcoreSlot D_800D07D8[];
extern WldcoreSlot D_800D07DC[];

void wldcore_clear_800d07d8_entry(s32 index) {
    D_800D07DC[index].value = 0;
    D_800D07D8[index].value = 0;
}
