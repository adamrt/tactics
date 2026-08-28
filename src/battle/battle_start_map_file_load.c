#include "psx/types.h"

enum {
    MAP_FILE_LOAD_LBA_OFFSET = 0x02,
    MAP_FILE_LOAD_BYTE_LENGTH_OFFSET = 0x06,
    MAP_FILE_LOAD_PRESENT_OFFSET = 0x0d,
};

extern s32 main_load_data_from_disc(s32 lba, s32 byte_length, s32 destination,
    s32 suppress_loading_display);

s32 battle_start_map_file_load(void* unused_file_table, u8* load_info,
    s32 destination, s32 suppress_loading_display) {
    if (load_info[MAP_FILE_LOAD_PRESENT_OFFSET] != 0) {
        /* Emits nothing. The target re-copies destination from $s0 into $a2
         * for the call; without this clobber GCC knows $a2 is still intact
         * and fills the delay slot with a nop instead (void * parameter and
         * cast forms behave the same). */
        asm volatile("" : : : "$6");
        if (main_load_data_from_disc(
                *(s32*)(load_info + MAP_FILE_LOAD_LBA_OFFSET),
                *(s32*)(load_info + MAP_FILE_LOAD_BYTE_LENGTH_OFFSET),
                destination, suppress_loading_display)
            == 0) {
            return destination;
        }
    }
    return 0;
}
