#include "psx/types.h"

extern s32 g_map_mesh_data_buffer;
extern s32 g_textured_triangle_render_record_count;
extern s32 g_textured_quad_render_record_count;
extern s32 g_untextured_triangle_render_record_count;
extern s32 g_untextured_quad_render_record_count;
extern u8* g_battle_data;

/*
 * Runtime polygon records interleave GPU packet fields with renderer state.
 * This pass skips the geometry and normal vectors consumed by
 * battle_append_map_mesh_geometry, then appends UV coordinates, CLUT commands,
 * texture-page commands, and the initial state of untextured records.
 */
typedef struct TexturedTriangleRenderRecord {
    u8 _unknown00[0x0c];
    u8 u0;
    u8 v0;
    u16 clut;
    u8 _unknown10[8];
    u8 u1;
    u8 v1;
    u16 texture_page;
    u8 _unknown1c[8];
    u8 u2;
    u8 v2;
    u8 _unknown26[2];
} TexturedTriangleRenderRecord;

typedef struct TexturedQuadRenderRecord {
    u8 u0;
    u8 v0;
    u16 clut;
    u8 _unknown04[8];
    u8 u1;
    u8 v1;
    u16 texture_page;
    u8 _unknown10[8];
    u8 u2;
    u8 v2;
    u8 _unknown1a[0x0a];
    u8 u3;
    u8 v3;
    u8 _unknown26[0x0e];
} TexturedQuadRenderRecord;

typedef struct UntexturedTriangleRenderTable {
    u8 _unknown00[0xc87c];
    struct {
        u8 state0;
        u8 state1;
        u8 is_active;
        u8 _unknown03[0x11];
    } record;
} UntexturedTriangleRenderTable;

typedef struct UntexturedQuadRenderTable {
    u8 _unknown00[0xcd7c];
    struct {
        u8 state0;
        u8 state1;
        u8 is_active;
        u8 _unknown03[0x15];
    } record;
} UntexturedQuadRenderTable;

#define TEXTURED_TRIANGLE_AT(byte_offset) \
    (*(TexturedTriangleRenderRecord*)(g_battle_data + (byte_offset)))
#define TEXTURED_QUAD_AT(byte_offset) \
    (*(TexturedQuadRenderRecord*)(g_battle_data + (byte_offset) + 0x384c))
#define UNTEXTURED_TRIANGLE_AT(byte_offset) \
    (((UntexturedTriangleRenderTable*)(g_battle_data + (byte_offset)))->record)
#define UNTEXTURED_QUAD_AT(byte_offset) \
    (((UntexturedQuadRenderTable*)(g_battle_data + (byte_offset)))->record)

void battle_initialize_map_mesh_render_records(u16* geometry_data) {
    u16* source = geometry_data;
    s32 polygon_index;
    s32 textured_triangle_count;
    s32 textured_quad_count;
    s32 untextured_triangle_count;
    s32 untextured_quad_count;
    s32 textured_record_offset;
    s32 untextured_record_offset;
    s32 triangle_vector_halfwords;
    s32 quad_vector_halfwords;

    polygon_index = g_textured_triangle_render_record_count;
    {
        s32 renderer_data;

        renderer_data = g_battle_data;
        g_map_mesh_data_buffer = renderer_data;
    }

    textured_triangle_count = *source++;
    textured_quad_count = *source++;
    untextured_triangle_count = *source++;
    untextured_quad_count = *source++;

    triangle_vector_halfwords = textured_triangle_count * 9;
    quad_vector_halfwords = textured_quad_count * 12;
    source += triangle_vector_halfwords + quad_vector_halfwords + untextured_triangle_count * 9 + untextured_quad_count * 12 + triangle_vector_halfwords + quad_vector_halfwords;

    if (polygon_index < textured_triangle_count + polygon_index) {
        s32 loop_condition;
        s32 record_offset_units;

        record_offset_units = polygon_index * 4;
        record_offset_units += polygon_index;
        textured_record_offset = record_offset_units * 8;
        /* Pins: the per-field temporaries and both record pointers are
         * hand-allocated. With every pin removed the function is the same
         * size but nearly every temporary lands in a different register
         * (and the target's $s0 save disappears); permuter territory. */
        do {
            register u16 packed asm("$3");
            register s32 u0 asm("$10");
            register s32 v0 asm("$12");
            register s32 u1 asm("$8");
            register s32 v1 asm("$11");
            register s32 v2 asm("$9");
            register u16 clut_data asm("$14");
            register u16 texture_page asm("$13");
            register u16 clut_command asm("$2");
            register TexturedTriangleRenderRecord* first_record asm("$2");
            TexturedTriangleRenderRecord* final_record;

            packed = *source++;
            first_record = (TexturedTriangleRenderRecord*)g_battle_data;
            v0 = packed >> 8;
            u0 = packed & 0xff;
            packed = *source++;
            clut_data = packed;
            packed = *source++;
            v1 = packed >> 8;
            u1 = packed & 0xff;
            packed = *source++;
            texture_page = packed;
            packed = *source;

            first_record = (TexturedTriangleRenderRecord*)((u8*)first_record + textured_record_offset);
            first_record->u0 = u0;
            TEXTURED_TRIANGLE_AT(textured_record_offset).u1 = u1;
            TEXTURED_TRIANGLE_AT(textured_record_offset).u2 = packed;
            polygon_index++;
            TEXTURED_TRIANGLE_AT(textured_record_offset).v0 = v0;
            source++;
            TEXTURED_TRIANGLE_AT(textured_record_offset).v1 = v1;
            v2 = packed >> 8;
            TEXTURED_TRIANGLE_AT(textured_record_offset).v2 = v2;
            clut_command = (clut_data & 0x3f) | 0x7800;
            final_record = (TexturedTriangleRenderRecord*)g_battle_data;
            final_record = (TexturedTriangleRenderRecord*)((u8*)final_record + textured_record_offset);
            textured_record_offset += 0x28;
            loop_condition = textured_triangle_count + g_textured_triangle_render_record_count;
            loop_condition = polygon_index < loop_condition;
            final_record->clut = clut_command;
            final_record->texture_page = texture_page;
        } while (loop_condition);
    }

    polygon_index = g_textured_quad_render_record_count;
    if (polygon_index < textured_quad_count + polygon_index) {
        s32 loop_condition;
        s32 record_offset_units;

        record_offset_units = polygon_index * 2;
        record_offset_units += polygon_index;
        record_offset_units *= 4;
        record_offset_units += polygon_index;
        textured_record_offset = record_offset_units * 4;
        do {
            u16 packed;
            register s32 u0 asm("$10");
            register s32 v0 asm("$12");
            register s32 u1 asm("$8");
            register s32 v1 asm("$11");
            register s32 u2 asm("$4");
            register s32 v2 asm("$9");
            register u16 clut_data asm("$14");
            register u16 texture_page asm("$13");
            register u16 clut_command asm("$2");
            register u8* first_record asm("$2");
            u8* final_record;

            packed = *source++;
            first_record = g_battle_data;
            v0 = packed >> 8;
            u0 = packed & 0xff;
            packed = *source++;
            clut_data = packed;
            packed = *source++;
            v1 = packed >> 8;
            u1 = packed & 0xff;
            packed = *source++;
            texture_page = packed;
            packed = *source++;
            v2 = packed >> 8;
            u2 = packed & 0xff;
            packed = *source;

            first_record += textured_record_offset;
            ((TexturedQuadRenderRecord*)(first_record + 0x384c))->u0 = u0;
            TEXTURED_QUAD_AT(textured_record_offset).u1 = u1;
            TEXTURED_QUAD_AT(textured_record_offset).u2 = u2;
            TEXTURED_QUAD_AT(textured_record_offset).u3 = packed;
            TEXTURED_QUAD_AT(textured_record_offset).v0 = v0;
            polygon_index++;
            TEXTURED_QUAD_AT(textured_record_offset).v1 = v1;
            source++;
            TEXTURED_QUAD_AT(textured_record_offset).v2 = v2;
            packed >>= 8;
            TEXTURED_QUAD_AT(textured_record_offset).v3 = packed;
            clut_command = (clut_data & 0x3f) | 0x7800;
            final_record = g_battle_data;
            final_record += textured_record_offset;
            textured_record_offset += 0x34;
            loop_condition = textured_quad_count + g_textured_quad_render_record_count;
            loop_condition = polygon_index < loop_condition;
            ((TexturedQuadRenderRecord*)(final_record + 0x384c))->clut = clut_command;
            ((TexturedQuadRenderRecord*)(final_record + 0x384c))->texture_page = texture_page;
        } while (loop_condition);
    }

    polygon_index = g_untextured_triangle_render_record_count;
    if (polygon_index < untextured_triangle_count + polygon_index) {
        s32 record_offset_units;
        s32 active;

        record_offset_units = polygon_index * 4;
        active = 1;
        record_offset_units += polygon_index;
        untextured_record_offset = record_offset_units * 4;
        do {
            UNTEXTURED_TRIANGLE_AT(untextured_record_offset).state0 = 0;
            UNTEXTURED_TRIANGLE_AT(untextured_record_offset).state1 = 0;
            polygon_index++;
            UNTEXTURED_TRIANGLE_AT(untextured_record_offset).is_active = active;
            untextured_record_offset += 0x14;
        } while (polygon_index < untextured_triangle_count + g_untextured_triangle_render_record_count);
    }

    polygon_index = g_untextured_quad_render_record_count;
    if (polygon_index < untextured_quad_count + polygon_index) {
        s32 record_offset_units;
        s32 active;

        active = 1;
        record_offset_units = polygon_index * 2;
        record_offset_units += polygon_index;
        untextured_record_offset = record_offset_units * 8;
        do {
            UNTEXTURED_QUAD_AT(untextured_record_offset).state0 = 0;
            UNTEXTURED_QUAD_AT(untextured_record_offset).state1 = 0;
            polygon_index++;
            UNTEXTURED_QUAD_AT(untextured_record_offset).is_active = active;
            untextured_record_offset += 0x18;
        } while (polygon_index < untextured_quad_count + g_untextured_quad_render_record_count);
    }
}
