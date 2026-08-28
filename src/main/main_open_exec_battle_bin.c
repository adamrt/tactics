#include "psx/types.h"

extern u8* g_low_overlay_load_address;
extern u8* g_high_overlay_load_address;

extern void* main_get_dat_as_wd(int sector, int size, void* destination);
extern void main_call_battle_bin_entrypoint(void);

void main_open_exec_battle_bin(void) {
    main_get_dat_as_wd(1000, g_high_overlay_load_address - g_low_overlay_load_address, g_low_overlay_load_address);
    main_call_battle_bin_entrypoint();
}
