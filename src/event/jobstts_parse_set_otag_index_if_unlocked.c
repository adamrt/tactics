#include "psx/types.h"

extern s8 g_jobstts_otag_index_locked;
extern s16 g_jobstts_otag_index;

const u8* jobstts_parse_set_otag_index_if_unlocked(const u8* data) {
    if (g_jobstts_otag_index_locked == 0) {
        g_jobstts_otag_index = data[3];
    }
    return data + data[1];
}
