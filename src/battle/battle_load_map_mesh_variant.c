#include "fft/map.h"

typedef struct PackedGnsRecord {
    u8 bytes[0x14];
} PackedGnsRecord;

enum {
    MAP_MESH_LOAD_IDLE = 0,
    MAP_MESH_LOAD_WAITING = 0x8d,
};

extern s32 battle_get_script_variable(s16 script_variable_id);
extern s32 battle_gns_record_matches_map_state(u8 comparison, s16 record_state,
    s16 requested_state);
extern void* game_malloc(s32 byte_length);
extern void main_game_free(void* allocation);
extern s32 main_check_file_still_loading(void);
extern void main_malloc_exception_handler(s32 allocator_id, s32 source_line);
extern s32 battle_start_map_file_load(void* unused_file_table, u8* load_info,
    void* destination,
    s32 suppress_loading_display);
extern void update_map_palette_from_color_data(s32, s32, s32, s32, void*);

extern s32 g_map_mesh_load_state;
extern PackedGnsRecord g_selected_map_mesh_record;
extern gns_file_record_t g_map_gns_records[];
extern u8 g_first_gns_resource_type;
extern void* g_map_mesh_load_buffer;
extern u8 g_map_file_table[];

s32 battle_load_map_mesh_variant(s32 mesh_slot) {
    switch (g_map_mesh_load_state) {
    case MAP_MESH_LOAD_IDLE:
        if (g_first_gns_resource_type < 0x80) {
            {
                u8* record_data;
                u8* resource_type;
                PackedGnsRecord* record;
                PackedGnsRecord* selected_record;
                /* Pin: unpinned, GCC hoists the 0x2e compare constant into
                 * $t0 instead of $t1 (register swap only, same size). */
                register s32 primary_resource_type asm("$9");

                selected_record = &g_selected_map_mesh_record;
                primary_resource_type = GNS_RESOURCE_MESH_PRIMARY;
                record_data = (u8*)&g_map_gns_records[0];
                resource_type = record_data + 5;
                record = (PackedGnsRecord*)record_data;
                do {
                    if (*resource_type == primary_resource_type) {
                        *selected_record = *record;
                    }
                    resource_type += sizeof(PackedGnsRecord);
                    record++;
                } while (*resource_type < 0x80);
            }

            if (g_first_gns_resource_type < 0x80) {
                u8* resource_type;
                s32 record_offset;
                s32 map_state;
                s32 map_state_and_weather;

                resource_type = (u8*)&g_map_gns_records[0] + 5;
                record_offset = 0;
                do {
                    if (*resource_type == GNS_RESOURCE_MESH_ALTERNATE) {
                        map_state = battle_get_script_variable(*(s16*)((u8*)&g_map_gns_records[0] + record_offset)) & 0xfff;
                        map_state_and_weather = map_state | ((battle_get_script_variable(0x23) & 7) << 12);
                        if ((battle_gns_record_matches_map_state(
                                 *((u8*)&g_map_gns_records[0] + record_offset + 4),
                                 *(s16*)((u8*)&g_map_gns_records[0] + record_offset + 2),
                                 map_state_and_weather | ((battle_get_script_variable(0x24) & 1) << 15))
                                << 16)
                            != 0) {
                            g_selected_map_mesh_record = *(PackedGnsRecord*)((u8*)&g_map_gns_records[0] + record_offset);
                        }
                    }
                    resource_type += sizeof(PackedGnsRecord);
                    record_offset += sizeof(PackedGnsRecord);
                } while (*resource_type < 0x80);
            }
        }

        g_map_mesh_load_buffer = game_malloc(0x20000);
        if (g_map_mesh_load_buffer == 0) {
            main_malloc_exception_handler(2, 0x3c9);
        }
        battle_start_map_file_load(g_map_file_table,
            &g_selected_map_mesh_record.bytes[6],
            g_map_mesh_load_buffer, 0x30);
        g_map_mesh_load_state = MAP_MESH_LOAD_WAITING;
        break;

    case MAP_MESH_LOAD_WAITING:
        if (main_check_file_still_loading() != 0) {
            s32 mesh_data_offset;
            void* mesh_data;

            mesh_data = g_map_mesh_load_buffer;
            mesh_data_offset = *(s32*)((u8*)mesh_data + 0x44) * 4;
            mesh_data = (void*)((s32)mesh_data + mesh_data_offset);
            update_map_palette_from_color_data(mesh_slot, 1, 0, 1, mesh_data);
            main_game_free(g_map_mesh_load_buffer);
            g_map_mesh_load_state = MAP_MESH_LOAD_IDLE;
        }
        break;
    }
    return g_map_mesh_load_state;
}
