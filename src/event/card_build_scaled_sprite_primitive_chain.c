#include "psx/types.h"

extern void SetPolyFT4(void* poly);
extern void SetPolyF4(void* poly);
extern u16 GetClut(s32 x, s32 y);
extern void SetSemiTrans(void* poly, s32 enabled);
extern void SetShadeTex(void* poly, s32 enabled);
extern void card_set_scaled_poly_ft4_geometry_and_uv(
    void* poly, const void* texture, const s16* position, const s16* uv,
    const s16* scale, const void* offset);

extern u8 g_card_scaled_sprite_count;
extern s16 g_card_scaled_sprite_scale[];
extern u8 g_card_scaled_sprite_texture_page[];
extern s16 g_card_primitive_tail_template[];
extern s16 g_card_scaled_sprite_uv_rects[];

void card_build_scaled_sprite_primitive_chain(u8* descriptor, u8* poly) {
    struct {
        s16 x;
        s16 y;
        u32 padding[2];
    } scale;
    s32 count;
    /* Pins: the target hoists both link masks into $s6/$s7 around these
     * three loop registers; the P_TAG setaddr/getaddr form compiles to the
     * same `and`s but re-allocates cursor/colour/uv (verified). */
    register u8* cursor __asm__("$16") = poly;
    s32 entry;
    s32 scale_offset;
    register s32 uv_offset __asm__("$21");
    register u8* color __asm__("$18");

    entry = 0;
    count = g_card_scaled_sprite_count;
    if (count > 0) {
        u32 address_mask = 0x00ffffff;
        u32 command_mask = 0xff000000;

        uv_offset = 0;
        scale_offset = 0;
        color = poly + 6;
        do {
            s32 x;
            s32 y;
            s32 rounded;

            SetPolyFT4(cursor);
            *(u16*)(color + 8) = GetClut(0, 0x1fd);
            color[-2] = descriptor[4];
            color[-1] = descriptor[4];
            color[0] = descriptor[4];
            SetSemiTrans(cursor, 1);
            SetShadeTex(cursor, 0);

            x = *(s16*)((u8*)g_card_scaled_sprite_scale + scale_offset);
            x *= *(s16*)(descriptor + 0xc);
            y = *(s16*)((u8*)g_card_scaled_sprite_scale + scale_offset + 2);
            y *= *(s16*)(descriptor + 0xe);
            rounded = x;
            if (x < 0)
                rounded = x + 0xfff;
            if (x - ((rounded >> 12) << 12) >= 0x800)
                x++;
            rounded = y;
            if (y < 0)
                rounded = y + 0xfff;
            if (y - ((rounded >> 12) << 12) >= 0x800)
                y++;
            rounded = x;
            if (x < 0)
                rounded = x + 0xfff;
            x = rounded >> 12;
            rounded = y;
            if (y < 0)
                rounded = y + 0xfff;
            y = rounded >> 12;
            scale.x = x;
            scale.y = y;
            card_set_scaled_poly_ft4_geometry_and_uv(
                cursor, g_card_scaled_sprite_texture_page,
                g_card_primitive_tail_template,
                (s16*)((u8*)g_card_scaled_sprite_uv_rects + uv_offset), &scale.x,
                descriptor + 0x18);
            uv_offset += 12;
            if (*(s32*)(descriptor + 8) != 0) {
                color += 0x28;
                {
                    u32* next = *(u32**)descriptor;
                    u32 poly_value = *(u32*)cursor;
                    u32 next_value = *next;

                    poly_value = (poly_value & command_mask) | (next_value & address_mask);
                    *(u32*)cursor = poly_value;
                }
                {
                    u32* next = *(u32**)descriptor;
                    register u32 poly_address __asm__("$4") = (u32)cursor & address_mask;
                    u32 next_value = *next;

                    cursor += 0x28;
                    next_value = (next_value & command_mask) | poly_address;
                    *next = next_value;
                }
            }
            scale_offset += 4;
        } while (++entry < g_card_scaled_sprite_count);
    }

    SetPolyF4(cursor);
    cursor[4] = 8;
    cursor[5] = 8;
    cursor[6] = 8;
    SetSemiTrans(cursor, 1);
    SetShadeTex(cursor, 0);
    *(s16*)(cursor + 8) = 0;
    *(s16*)(cursor + 0xa) = 0;
    {
        register u32 address_mask __asm__("$4") = 0x00ffffff;
        s32 max_coordinate = 0xff;
        u32 command_mask = 0xff000000;

        *(s16*)(cursor + 0x10) = max_coordinate;
        *(s16*)(cursor + 0x12) = 0;
        *(s16*)(cursor + 0x18) = 0;
        *(s16*)(cursor + 0x1a) = max_coordinate;
        *(s16*)(cursor + 0x20) = max_coordinate;
        *(s16*)(cursor + 0x22) = max_coordinate;

        *(u32*)cursor = (*(u32*)cursor & command_mask) | (**(u32**)descriptor & address_mask);
        **(u32**)descriptor = (**(u32**)descriptor & command_mask) | ((u32)cursor & address_mask);
    }
}
