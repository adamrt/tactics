#include "psx/types.h"

extern s32 CdControl(s32 command, const void* parameter, void* result);
extern s32 CdRead2(s32 mode);

void open_start_cd_stream_read(const void* location) {
    for (;;) {
        while (CdControl(2, location, 0) == 0) {
        }
        if (CdRead2(0x1a0) != 0) {
            break;
        }
    }
}
