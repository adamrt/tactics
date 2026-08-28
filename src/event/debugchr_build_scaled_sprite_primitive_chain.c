#include "psx/gpu.h"
#include "psx/types.h"

typedef struct DebugChrScaledSprite {
    u32* ordering_tag;
    u8 intensity;
    u8 pad_05[3];
    s32 link_primitive;
    s16 scale_x;
    s16 scale_y;
    u8 pad_10[8];
    s16 offset[6];
} DebugChrScaledSprite;

typedef struct DebugChrTexturePage {
} DebugChrTexturePage;

extern u8 g_debugchr_scaled_sprite_count;
extern s16 g_debugchr_scaled_sprite_scale[];
extern s16 g_debugchr_scaled_sprite_uv_rects[];
extern s16 g_debugchr_primitive_tail_template[];
extern DebugChrTexturePage g_debugchr_scaled_sprite_texture_page;

extern void debugchr_set_scaled_poly_ft4_geometry_and_uv(
    u8* poly, const DebugChrTexturePage* texture, const s16* position,
    const s16* uv_rect, const s16* scale, const s16* offset);

void debugchr_build_scaled_sprite_primitive_chain(
    DebugChrScaledSprite* sprite, u8* primitive_argument) {
    register u8* primitive __asm__("$16") = primitive_argument;
    s32 initial_count = g_debugchr_scaled_sprite_count;
    s32 i = 0;

    if (initial_count > 0) {
        u32 low_mask = 0xffffff;
        u32 high_mask = 0xff000000;
        register s32 uv_offset __asm__("$21") = 0;
        s32 scale_offset = 0;
        register u8* primitive_fields __asm__("$18") = primitive_argument + 6;
        do {
            register s32 scaled_x;
            register s32 scaled_y;
            s16 scaled[6];

            SetPolyFT4((POLY_FT4*)primitive);
            *(u16*)(primitive_fields + 8) = GetClut(0, 0x1fd);
            primitive_fields[-2] = sprite->intensity;
            primitive_fields[-1] = sprite->intensity;
            primitive_fields[0] = sprite->intensity;
            SetSemiTrans(primitive, 1);
            SetShadeTex(primitive, 0);

            scaled_x = *(s16*)((u8*)g_debugchr_scaled_sprite_scale + scale_offset);
            scaled_x *= sprite->scale_x;
            scaled_y = *(s16*)((u8*)g_debugchr_scaled_sprite_scale + scale_offset + 2) * sprite->scale_y;
            if (scaled_x % 4096 >= 2048)
                scaled_x++;
            if (scaled_y % 4096 >= 2048)
                scaled_y++;
            scaled_x /= 4096;
            scaled_y /= 4096;
            scaled[0] = scaled_x;
            scaled[1] = scaled_y;
            scaled_x = sizeof(POLY_FT4);

            debugchr_set_scaled_poly_ft4_geometry_and_uv(
                primitive, &g_debugchr_scaled_sprite_texture_page,
                g_debugchr_primitive_tail_template,
                (s16*)((u8*)g_debugchr_scaled_sprite_uv_rects + uv_offset),
                scaled, sprite->offset);
            uv_offset += 12;

            if (sprite->link_primitive != 0) {
                u32 primitive_tag;
                register u32 ordering_tag __asm__("$2");
                register u32 masked_primitive __asm__("$4");
                primitive_fields += scaled_x;
                primitive_tag = *(u32*)primitive;
                ordering_tag = *sprite->ordering_tag;
                *(u32*)primitive = (primitive_tag & high_mask) | (ordering_tag & low_mask);
                primitive_tag = (u32)sprite->ordering_tag;
                masked_primitive = (u32)primitive & low_mask;
                ordering_tag = *(u32*)primitive_tag;
                ordering_tag &= high_mask;
                ordering_tag |= masked_primitive;
                *(u32*)primitive_tag = ordering_tag;
                primitive += sizeof(POLY_FT4);
            }
            scale_offset += 4;
            i++;
        } while (i < g_debugchr_scaled_sprite_count);
    }

    SetPolyF4((POLY_F4*)primitive);
    primitive[4] = 8;
    primitive[5] = 8;
    primitive[6] = 8;
    SetSemiTrans(primitive, 1);
    SetShadeTex(primitive, 0);
    *(s16*)(primitive + 8) = 0;
    *(s16*)(primitive + 0xa) = 0;
    *(s16*)(primitive + 0x10) = 0xff;
    *(s16*)(primitive + 0x12) = 0;
    *(s16*)(primitive + 0x18) = 0;
    *(s16*)(primitive + 0x1a) = 0xff;
    *(s16*)(primitive + 0x20) = 0xff;
    *(s16*)(primitive + 0x22) = 0xff;
    {
        register u32 low_mask __asm__("$4") = 0xffffff;
        u32 high_mask = 0xff000000;
        *(u32*)primitive = (*(u32*)primitive & high_mask) | (*sprite->ordering_tag & low_mask);
        *sprite->ordering_tag = (*sprite->ordering_tag & high_mask) | ((u32)primitive & low_mask);
    }
}
