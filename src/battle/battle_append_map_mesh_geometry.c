#include "psx/types.h"

/*
 * The geometry block starts with four polygon counts, then stores positions
 * for all four polygon classes, normals for textured polygons, per-polygon
 * render data, and finally terrain-tile locations for textured polygons.
 * Each position/normal vector occupies eight renderer bytes: XYZ followed by
 * a spare halfword.  The first position vector's spare halfword holds the
 * polygon's packed terrain-tile location.
 */
typedef struct MeshTrianglePositions {
    s16 x0, y0, z0;
    u16 terrain_tile;
    s16 x1, y1, z1;
    u16 _pad0e;
    s16 x2, y2, z2;
    u16 _pad16;
} MeshTrianglePositions;

typedef struct MeshQuadPositions {
    s16 x0, y0, z0;
    u16 terrain_tile;
    s16 x1, y1, z1;
    u16 _pad0e;
    s16 x2, y2, z2;
    u16 _pad16;
    s16 x3, y3, z3;
    u16 _pad1e;
} MeshQuadPositions;

typedef struct MeshTriangleNormals {
    s16 x0, y0, z0;
    u16 _pad06;
    s16 x1, y1, z1;
    u16 _pad0e;
    s16 x2, y2, z2;
    u16 _pad16;
} MeshTriangleNormals;

typedef struct MeshQuadNormals {
    s16 x0, y0, z0;
    u16 _pad06;
    s16 x1, y1, z1;
    u16 _pad0e;
    s16 x2, y2, z2;
    u16 _pad16;
    s16 x3, y3, z3;
    u16 _pad1e;
} MeshQuadNormals;

typedef struct MapMeshPartMetadata {
    u8 _unknown00[0x88];
    u16 textured_triangle_start;
    u16 textured_quad_start;
    u16 untextured_triangle_start;
    u16 untextured_quad_start;
    u16 textured_triangle_count;
    u16 textured_quad_count;
    u16 untextured_triangle_count;
    u16 untextured_quad_count;
} MapMeshPartMetadata;

extern s32 g_textured_triangle_count;
extern s32 g_textured_quad_count;
extern s32 g_untextured_triangle_count;
extern s32 g_untextured_quad_count;
extern s32 g_map_resource_load_state;
extern s32 g_map_mesh_data_buffer;
extern s32 g_battle_data;
extern MeshTrianglePositions g_textured_triangle_positions[];
extern MeshQuadPositions g_textured_quad_positions[];
extern MeshTrianglePositions g_untextured_triangle_positions[];
extern MeshQuadPositions g_untextured_quad_positions[];
extern MeshTriangleNormals g_textured_triangle_normals[];
extern MeshQuadNormals g_textured_quad_normals[];

#define READ_GEOMETRY_HALFWORD() (*source++)
#define COPY_GEOMETRY_HALFWORD(symbol) \
    (*(u16*)((u8*)&(symbol) + destination_offset) = READ_GEOMETRY_HALFWORD())

void battle_append_map_mesh_geometry(u16* geometry_data,
    MapMeshPartMetadata* metadata) {
    u16* source = geometry_data;
    s32 index;
    s32 textured_triangle_count;
    s32 textured_quad_count;
    s32 untextured_triangle_count;
    register s32 untextured_quad_count asm("$12");
    register s32 polygon_end asm("$3");
    register s32 polygon_end_copy asm("$4");
    s32 destination_byte_end;
    s32 destination_offset;
    s32 has_polygons;
    u16 textured_triangle_start;
    register u16 textured_quad_start asm("$3");
    u16 untextured_triangle_start;
    u16 untextured_quad_start;
    s32 current_textured_triangles;
    s32 current_textured_quads;
    s32 current_untextured_triangles;
    s32 current_untextured_quads;
    s32 new_untextured_triangle_count;
    register s32 new_untextured_quad_count asm("$3");
    s32 renderer_state;

    /* Pins: with all five removed the function stays 1956 bytes but the loop
     * counters/bounds shift registers ($t0<->$t1, $t3<->$t4) and the first
     * bound computation is hoisted above the metadata stores. The two
     * memory fences below are load-bearing on their own: they keep the
     * g_map_resource_load_state store and the final count reload in the
     * target's order. */
    index = g_textured_triangle_count;
    renderer_state = g_battle_data;
    g_map_resource_load_state = 0x79;
    g_map_mesh_data_buffer = renderer_state;

    textured_triangle_start = g_textured_triangle_count;
    untextured_triangle_start = g_untextured_triangle_count;
    untextured_quad_start = g_untextured_quad_count;

    textured_triangle_count = READ_GEOMETRY_HALFWORD();
    textured_quad_count = READ_GEOMETRY_HALFWORD();
    untextured_triangle_count = READ_GEOMETRY_HALFWORD();
    untextured_quad_count = *source;

    __asm__ volatile("" : : : "memory");
    textured_quad_start = g_textured_quad_count;
    source++;
    metadata->textured_triangle_start = textured_triangle_start;
    metadata->untextured_triangle_start = untextured_triangle_start;
    metadata->untextured_quad_start = untextured_quad_start;
    metadata->textured_quad_start = textured_quad_start;
    metadata->textured_triangle_count = textured_triangle_count;
    metadata->textured_quad_count = textured_quad_count;
    metadata->untextured_triangle_count = untextured_triangle_count;
    metadata->untextured_quad_count = untextured_quad_count;

    polygon_end = textured_triangle_count + index;
    has_polygons = index < polygon_end;
    if (has_polygons) {
        polygon_end_copy = polygon_end;
        destination_offset = index * 0x18;
        do {
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_positions[0].x0);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_positions[0].y0);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_positions[0].z0);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_positions[0].x1);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_positions[0].y1);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_positions[0].z1);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_positions[0].x2);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_positions[0].y2);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_positions[0].z2);
            index++;
            destination_offset += 0x18;
        } while (index < polygon_end_copy);
    }

    index = g_textured_quad_count;
    destination_byte_end = textured_quad_count + index;
    destination_offset = index << 5;
    has_polygons = index < destination_byte_end;
    if (has_polygons) {
        destination_byte_end <<= 5;
        do {
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].x0);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].y0);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].z0);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].x1);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].y1);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].z1);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].x2);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].y2);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].z2);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].x3);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].y3);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].z3);
            destination_offset += 0x20;
        } while (destination_offset < destination_byte_end);
    }

    index = g_untextured_triangle_count;
    polygon_end = untextured_triangle_count + index;
    has_polygons = index < polygon_end;
    if (has_polygons) {
        polygon_end_copy = polygon_end;
        destination_offset = index * 0x18;
        do {
            COPY_GEOMETRY_HALFWORD(g_untextured_triangle_positions[0].x0);
            COPY_GEOMETRY_HALFWORD(g_untextured_triangle_positions[0].y0);
            COPY_GEOMETRY_HALFWORD(g_untextured_triangle_positions[0].z0);
            COPY_GEOMETRY_HALFWORD(g_untextured_triangle_positions[0].x1);
            COPY_GEOMETRY_HALFWORD(g_untextured_triangle_positions[0].y1);
            COPY_GEOMETRY_HALFWORD(g_untextured_triangle_positions[0].z1);
            COPY_GEOMETRY_HALFWORD(g_untextured_triangle_positions[0].x2);
            COPY_GEOMETRY_HALFWORD(g_untextured_triangle_positions[0].y2);
            COPY_GEOMETRY_HALFWORD(g_untextured_triangle_positions[0].z2);
            index++;
            destination_offset += 0x18;
        } while (index < polygon_end_copy);
    }

    index = g_untextured_quad_count;
    destination_byte_end = untextured_quad_count + index;
    destination_offset = index << 5;
    has_polygons = index < destination_byte_end;
    if (has_polygons) {
        destination_byte_end <<= 5;
        do {
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].x0);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].y0);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].z0);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].x1);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].y1);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].z1);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].x2);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].y2);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].z2);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].x3);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].y3);
            COPY_GEOMETRY_HALFWORD(g_untextured_quad_positions[0].z3);
            destination_offset += 0x20;
        } while (destination_offset < destination_byte_end);
    }

    index = g_textured_triangle_count;
    polygon_end = textured_triangle_count + index;
    has_polygons = index < polygon_end;
    if (has_polygons) {
        polygon_end_copy = polygon_end;
        destination_offset = index * 0x18;
        do {
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_normals[0].x0);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_normals[0].y0);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_normals[0].z0);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_normals[0].x1);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_normals[0].y1);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_normals[0].z1);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_normals[0].x2);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_normals[0].y2);
            COPY_GEOMETRY_HALFWORD(g_textured_triangle_normals[0].z2);
            index++;
            destination_offset += 0x18;
        } while (index < polygon_end_copy);
    }

    index = g_textured_quad_count;
    destination_byte_end = textured_quad_count + index;
    destination_offset = index << 5;
    has_polygons = index < destination_byte_end;
    if (has_polygons) {
        destination_byte_end <<= 5;
        do {
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].x0);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].y0);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].z0);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].x1);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].y1);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].z1);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].x2);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].y2);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].z2);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].x3);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].y3);
            COPY_GEOMETRY_HALFWORD(g_textured_quad_normals[0].z3);
            destination_offset += 0x20;
        } while (destination_offset < destination_byte_end);
    }

    /* Skip texture records (10/12 bytes) and untextured records (4 bytes). */
    source += textured_triangle_count * 5 + textured_quad_count * 6 + untextured_triangle_count * 2 + untextured_quad_count * 2;

    index = g_textured_triangle_count;
    polygon_end = textured_triangle_count + index;
    has_polygons = index < polygon_end;
    if (has_polygons) {
        polygon_end_copy = polygon_end;
        destination_offset = index * 0x18;
        do {
            COPY_GEOMETRY_HALFWORD(
                g_textured_triangle_positions[0].terrain_tile);
            index++;
            destination_offset += 0x18;
        } while (index < polygon_end_copy);
    }

    index = g_textured_quad_count;
    destination_byte_end = textured_quad_count + index;
    destination_offset = index << 5;
    has_polygons = index < destination_byte_end;
    if (has_polygons) {
        destination_byte_end <<= 5;
        do {
            COPY_GEOMETRY_HALFWORD(g_textured_quad_positions[0].terrain_tile);
            destination_offset += 0x20;
        } while (destination_offset < destination_byte_end);
    }

    current_textured_triangles = g_textured_triangle_count;
    current_textured_quads = g_textured_quad_count;
    g_textured_triangle_count = textured_triangle_count + current_textured_triangles;
    current_untextured_triangles = g_untextured_triangle_count;
    g_textured_quad_count = textured_quad_count + current_textured_quads;
    __asm__ volatile("" : : : "memory");
    current_untextured_quads = g_untextured_quad_count;
    new_untextured_triangle_count = untextured_triangle_count + current_untextured_triangles;
    new_untextured_quad_count = untextured_quad_count + current_untextured_quads;
    g_untextured_triangle_count = new_untextured_triangle_count;
    g_untextured_quad_count = new_untextured_quad_count;
}
