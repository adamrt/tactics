#ifndef FFT_MAP_H
#define FFT_MAP_H

#include "psx/types.h"

/* Low six bits of a terrain tile's first byte (FFHacktics page 00000089). */
typedef enum map_surface_type {
    MAP_SURFACE_NATURAL = 0x00,
    MAP_SURFACE_SAND = 0x01,
    MAP_SURFACE_STALACTITE = 0x02,
    MAP_SURFACE_GRASSLAND = 0x03,
    MAP_SURFACE_THICKET = 0x04,
    MAP_SURFACE_SNOW = 0x05,
    MAP_SURFACE_ROCKY_CLIFF = 0x06,
    MAP_SURFACE_GRAVEL = 0x07,
    MAP_SURFACE_WASTELAND = 0x08,
    MAP_SURFACE_SWAMP = 0x09,
    MAP_SURFACE_MARSH = 0x0a,
    MAP_SURFACE_POISONED_MARSH = 0x0b,
    MAP_SURFACE_LAVA_ROCKS = 0x0c,
    MAP_SURFACE_ICE = 0x0d,
    MAP_SURFACE_WATERWAY = 0x0e,
    MAP_SURFACE_RIVER = 0x0f,
    MAP_SURFACE_LAKE = 0x10,
    MAP_SURFACE_SEA = 0x11,
    MAP_SURFACE_LAVA = 0x12,
    MAP_SURFACE_ROAD = 0x13,
    MAP_SURFACE_WOODEN_FLOOR = 0x14,
    MAP_SURFACE_STONE_FLOOR = 0x15,
    MAP_SURFACE_ROOF = 0x16,
    MAP_SURFACE_STONE_WALL = 0x17,
    MAP_SURFACE_SKY = 0x18,
    MAP_SURFACE_DARKNESS = 0x19,
    MAP_SURFACE_SALT = 0x1a,
    MAP_SURFACE_BOOK = 0x1b,
    MAP_SURFACE_OBSTACLE = 0x1c,
    MAP_SURFACE_RUG = 0x1d,
    MAP_SURFACE_TREE = 0x1e,
    MAP_SURFACE_BOX = 0x1f,
    MAP_SURFACE_BRICK = 0x20,
    MAP_SURFACE_CHIMNEY = 0x21,
    MAP_SURFACE_MUD_WALL = 0x22,
    MAP_SURFACE_BRIDGE = 0x23,
    MAP_SURFACE_WATER_PLANT = 0x24,
    MAP_SURFACE_STAIRS = 0x25,
    MAP_SURFACE_FURNITURE = 0x26,
    MAP_SURFACE_IVY = 0x27,
    MAP_SURFACE_DECK = 0x28,
    MAP_SURFACE_MACHINE = 0x29,
    MAP_SURFACE_IRON_PLATE = 0x2a,
    MAP_SURFACE_MOSS = 0x2b,
    MAP_SURFACE_TOMBSTONE = 0x2c,
    MAP_SURFACE_WATERFALL = 0x2d,
    MAP_SURFACE_COFFIN = 0x2e,
    MAP_SURFACE_CROSS_SECTION = 0x3f,
} map_surface_type_t;

enum { MAP_SURFACE_MASK = 0x3f };

typedef enum gns_map_state_comparison {
    GNS_MAP_STATE_EQUAL = 1,
    GNS_MAP_STATE_REQUESTED_LESS_THAN_RECORD = 2,
    GNS_MAP_STATE_REQUESTED_GREATER_THAN_RECORD = 3,
} gns_map_state_comparison_t;

typedef enum gns_resource_type {
    GNS_RESOURCE_TEXTURE = 0x17,
    GNS_RESOURCE_MESH_PRIMARY = 0x2e,
    GNS_RESOURCE_MESH_OVERRIDE = 0x2f,
    GNS_RESOURCE_MESH_ALTERNATE = 0x30,
    GNS_RESOURCE_END = 0x31,
    GNS_RESOURCE_SET_INDOOR = 0x85,
    GNS_RESOURCE_SET_OUTDOOR = 0x86,
    GNS_RESOURCE_CLEAR_SNOW = 0x88,
    GNS_RESOURCE_SET_SNOW = 0x89,
    GNS_RESOURCE_RESERVED_8A = 0x8a,
    GNS_RESOURCE_SET_WEATHER_MODIFIER = 0x8b,
} gns_resource_type_t;

typedef struct map_move_find_item_data {
    u8 data[0x10];
} map_move_find_item_data_t;

enum {
    MAP_PALETTE_ROW_COUNT = 16,
    MAP_PALETTE_COLORS_PER_ROW = 16,
    MAP_PALETTE_COLOR_COUNT = 256,
};

/* Unscaled components decoded from one PlayStation ABBBBBGGGGGRRRRR word. */
typedef struct map_palette_color_components {
    u8 red_5bit;
    u8 green_5bit;
    u8 blue_5bit;
    u8 alpha_bit;
    u8 _unknown04[3];
} map_palette_color_components_t;

typedef struct map_palette_animation_state {
    u8 active;
    u8 _unknown01[7];
} map_palette_animation_state_t;

/* One 0x982-byte runtime bank is maintained for each loaded map mesh. */
typedef struct map_palette_runtime_bank {
    u8 _unknown00;
    u8 updates_disabled;
    map_palette_animation_state_t animations[MAP_PALETTE_ROW_COUNT];
    map_palette_color_components_t components[MAP_PALETTE_COLOR_COUNT];
    u16 packed_colors[MAP_PALETTE_COLOR_COUNT];
} map_palette_runtime_bank_t;

typedef char MapPaletteColorComponents_size_must_be_7[(sizeof(map_palette_color_components_t) == 7) ? 1 : -1];
typedef char MapPaletteAnimationState_size_must_be_8[(sizeof(map_palette_animation_state_t) == 8) ? 1 : -1];
typedef char MapPaletteRuntimeBank_size_must_be_0x982[(sizeof(map_palette_runtime_bank_t) == 0x982) ? 1 : -1];

/*
 * A 20-byte record from MAPnnn.GNS.  For mesh records, the loader compares
 * map_state against a request assembled from the low 12 bits of the script
 * variable at offset 0, weather in bits 12-14, and time-of-day in bit 15.
 *
 * The two bytes at 4 also form the conventional little-endian GNS record type
 * (for example, 0x2e01 for a primary mesh).  The game reads them separately:
 * the low byte selects the state comparison and the high byte selects the
 * resource type.
 */
typedef struct gns_file_record {
    u16 script_variable_id;  /* 0x00 */
    s16 map_state;           /* 0x02 */
    u8 map_state_comparison; /* 0x04; gns_map_state_comparison_t */
    u8 resource_type;        /* 0x05; gns_resource_type_t */
    u16 _unknown06;
    u16 start_sector; /* 0x08; relative to the MAPnnn.GNS LBA */
    u16 _unknown0a;
    u32 byte_length; /* 0x0c; sector-rounded */
    u16 _unknown10;
    u16 _unknown12;
} gns_file_record_t;

typedef char GnsFileRecord_size_must_be_0x14[(sizeof(gns_file_record_t) == 0x14) ? 1 : -1];

#endif
