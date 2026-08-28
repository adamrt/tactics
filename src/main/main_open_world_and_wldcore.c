#include "psx/types.h"

extern void* g_low_overlay_load_address;
extern void* g_world_overlay_load_address;

extern void main_load_data_from_disc(int sector, int sectors, void* destination, int suppress_loading_display);
extern int world_bin_entrypoint(void);

int main_open_world_and_wldcore(int load_world) {
    main_load_data_from_disc(0x14849, 0xdc, g_low_overlay_load_address, 0);
    if (load_world != 0) {
        main_load_data_from_disc(0x14925, 0x1e0, g_world_overlay_load_address, 1);
    }
    return world_bin_entrypoint();
}
