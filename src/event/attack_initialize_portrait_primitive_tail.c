#include "psx/types.h"

typedef struct AttackPortraitPrimitiveTail {
    u8 unknown_00[0x1c];
    s16 unknown_1c;
    u8 unknown_1e[8];
    s16 unknown_26;
} AttackPortraitPrimitiveTail;

extern const u8 g_attack_primitive_tail_template[8];
extern void world_copy_bytes(void* destination, const void* source, s32 size);

void attack_initialize_portrait_primitive_tail(AttackPortraitPrimitiveTail* data) {
    data->unknown_1c = 0;
    data->unknown_26 = 0;
    world_copy_bytes(&data->unknown_1e[2], g_attack_primitive_tail_template, 8);
}
