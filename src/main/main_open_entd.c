#include "fft/data.h"

enum {
    ENTD_SET_BYTES = 0x14000,
    ENTD2_FIRST_EVENT = 0x80,
    ENTD3_FIRST_EVENT = 0x100,
    ENTD4_FIRST_EVENT = 0x180,
    ENTD1_LBA = 0xebc1,
    ENTD2_LBA = 0xebe9,
    ENTD3_LBA = 0xec11,
    ENTD4_LBA = 0xec39,
};

extern int g_current_event_id;
extern entd_file_t* g_entd_set;

extern entd_file_t* game_malloc(int size);
extern int main_load_data_from_disc(int lba, int size, void* destination);
extern void game_free_with_extra_steps(void* allocation);

int main_open_entd(void) {
    int lba;
    entd_file_t* entd_set;

    if (g_current_event_id == 0) {
        goto success;
    }

    if (g_current_event_id < ENTD2_FIRST_EVENT) {
        entd_set = game_malloc(ENTD_SET_BYTES);
        g_entd_set = entd_set;
        lba = ENTD1_LBA;
    } else if (g_current_event_id < ENTD3_FIRST_EVENT) {
        entd_set = game_malloc(ENTD_SET_BYTES);
        g_entd_set = entd_set;
        lba = ENTD2_LBA;
    } else if (g_current_event_id < ENTD4_FIRST_EVENT) {
        entd_set = game_malloc(ENTD_SET_BYTES);
        g_entd_set = entd_set;
        lba = ENTD3_LBA;
    } else {
        entd_set = game_malloc(ENTD_SET_BYTES);
        g_entd_set = entd_set;
        lba = ENTD4_LBA;
    }

    if (main_load_data_from_disc(lba, ENTD_SET_BYTES, entd_set) == 0) {
        goto success;
    }

    game_free_with_extra_steps(g_entd_set);
    return 0;

success:
    return 1;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
