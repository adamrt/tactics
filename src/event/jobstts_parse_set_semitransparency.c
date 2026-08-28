#include "psx/types.h"

extern s16 g_jobstts_semitransparency;

const u8* jobstts_parse_set_semitransparency(const u8* data) {
    g_jobstts_semitransparency = data[3];
    return data + data[1];
}
