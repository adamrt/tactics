#include "fft/map.h"

enum {
    GNS_INITIAL_LOAD_BYTES = 0x1000,
    GNS_BUFFER_CLEAR_BYTES = 0xbb8,
};

extern map_move_find_item_data_t g_map_move_find_item_data[];
extern u32 g_map_gns_lba[];
extern void* g_map_data_load_buffer;
extern gns_file_record_t g_map_gns_records[];

extern void battle_load_move_find_item_data(map_move_find_item_data_t* map_data);
extern void* bzero(void* destination, s32 byte_length);
extern s32 main_load_data_from_disc(s32 lba, s32 byte_length, void* destination);

gns_file_record_t* battle_load_map_gns_and_move_find_items(s32 map_id) {
    u32 selected_map;
    gns_file_record_t* gns_records;
    u32 lba;

    selected_map = map_id & 0xffff;
    battle_load_move_find_item_data(&g_map_move_find_item_data[selected_map]);

    gns_records = g_map_gns_records;
    bzero(gns_records, GNS_BUFFER_CLEAR_BYTES);

    lba = g_map_gns_lba[selected_map];
    if (lba != 0) {
        if (main_load_data_from_disc(lba, GNS_INITIAL_LOAD_BYTES,
                g_map_data_load_buffer)
            != 0) {
            return 0;
        }
        return gns_records;
    }
    /* The target falls through with the BIOS bzero result still in v0. */
}
