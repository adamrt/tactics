#include "psx/cd.h"
#include "psx/types.h"

extern u8 g_cd_file_state;
extern u32 g_file_still_loading;

extern void main_reset_pause_cdrom(u8*);

void main_reset_cdrom_cpu_ram(void) {
    SetMem(2);
    CdInit();
    CdSetDebug(0);
    main_reset_pause_cdrom(&g_cd_file_state);
    g_file_still_loading = 0;
}
