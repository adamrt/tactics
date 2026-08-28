#include "psx/types.h"

typedef struct EquipPortraitPrimitiveTail {
    u8 unknown_00[0x1c];
    s16 unknown_1c;
    u8 unknown_1e[8];
    s16 unknown_26;
} EquipPortraitPrimitiveTail;

extern const u8 D_801CE7F8[8];
extern void world_copy_bytes(void* destination, const void* source, s32 size);

void equip_reset_portrait_primitive_tail(EquipPortraitPrimitiveTail* data) {
    data->unknown_1c = 0;
    data->unknown_26 = 0;
    world_copy_bytes(&data->unknown_1e[2], D_801CE7F8, 8);
}
