#include "psx/types.h"

extern s32 g_open_pending_file_status;

extern void open_file_to_ram_center(void* file_header);
extern s32 VSync(s32 mode);

void open_wait_for_pending_file(void) {
    s32* status = &g_open_pending_file_status;
    void* header;

    if (*status == 0) {
        return;
    }

    header = (u8*)status - 4;
    do {
        open_file_to_ram_center(header);
        VSync(0);
    } while (g_open_pending_file_status != 0);
}
