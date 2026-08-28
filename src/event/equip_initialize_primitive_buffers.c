#include "psx/gpu.h"
#include "psx/types.h"

extern u16 g_equip_line_f2_capacity;
extern u16 g_equip_poly_f4_capacity;
extern u16 g_equip_poly_ft4_capacity;
extern u16 g_equip_tile_capacity;
extern u16 g_equip_draw_move_capacity;

void equip_initialize_primitive_buffers(u8* arg0) {
    s32 i;

    for (i = 0; i < (s32)g_equip_line_f2_capacity; i++) {
        SetLineF2((void*)((i * 0x10) + *(s32*)(arg0 + 0x24)));
    }
    for (i = 0; i < (s32)g_equip_poly_f4_capacity; i++) {
        SetPolyF4((POLY_F4*)((i * 0x18) + *(s32*)(arg0 + 0xC)));
        SetShadeTex((void*)((i * 0x18) + *(s32*)(arg0 + 0xC)), 0);
    }
    for (i = 0; i < (s32)g_equip_poly_ft4_capacity; i++) {
        SetPolyFT4((POLY_FT4*)((i * 0x28) + *(s32*)(arg0 + 0x10)));
        SetShadeTex((void*)((i * 0x28) + *(s32*)(arg0 + 0x10)), 0);
    }
    for (i = 0; i < (s32)g_equip_tile_capacity; i++) {
        SetTile((void*)((i * 0x10) + *(s32*)(arg0 + 0x3C)));
    }
    for (i = 0; i < (s32)g_equip_draw_move_capacity; i++) {
        SetDrawMove((void*)((i * 0x18) + *(s32*)(arg0 + 0x58)));
    }
}
