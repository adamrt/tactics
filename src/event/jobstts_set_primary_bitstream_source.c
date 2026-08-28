#include "psx/types.h"

extern u8 g_jobstts_primary_bitstream_reset;
extern const u8* g_jobstts_primary_bitstream_source;

void jobstts_set_primary_bitstream_source(const u8* data) {
    g_jobstts_primary_bitstream_reset = 1;
    g_jobstts_primary_bitstream_source = data;
}
