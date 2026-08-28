#include "psx/etc.h"
#include "psx/types.h"

extern u8 g_file_header[];
extern s32 g_file_still_loading;

extern void* game_malloc(s32 size);
extern void main_animation_exception_handler(s32 error_code);
extern s32 main_build_file_header_nnl(u8* header, s32 sector, s32 sector_count, void* destination);
extern void tick(void);
extern void open_file_to_ram_center(u8* header);

/* Allocates a game-heap buffer for a TIM of `size` bytes at disc `sector`,
 * queues the read and blocks until the file has landed.  Twin of
 * main_get_smd, which draws from the SMD allocator instead. */
void* main_get_tim(s32 sector, s32 size) {
    void* destination;
    u8* header;

    destination = game_malloc(size);
    if (destination == 0) {
        main_animation_exception_handler(1);
    }
    while (main_build_file_header_nnl(g_file_header, sector, (s32)((u32)size >> 11), destination) != 0) {
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
    return destination;
}
