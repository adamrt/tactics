#include "psx/types.h"

extern void* smd_malloc(int size);
extern void main_animation_exception_handler(int code);
extern int main_build_file_header_nnl(void* header, int sector, int sectors,
    void* destination);
extern void VSync(int mode);
extern void tick(void);
extern void open_file_to_ram_center(void* header);

extern u8 g_file_header[];
extern int g_file_still_loading;

void* main_get_smd(int sector, int size) {
    void* buffer;
    u8* header;

    buffer = smd_malloc(size);
    if (buffer == 0) {
        main_animation_exception_handler(0x11);
    }
    while (main_build_file_header_nnl(g_file_header, sector, (u32)size >> 11,
               buffer)
        != 0) {
        VSync(0);
        tick();
        open_file_to_ram_center(g_file_header);
    }
    if (g_file_still_loading != 0) {
        header = g_file_header;
        do {
            VSync(0);
            tick();
            open_file_to_ram_center(header);
        } while (g_file_still_loading != 0);
    }
    return buffer;
}
