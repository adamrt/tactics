#include "psx/gpu.h"
#include "psx/types.h"

extern RECT g_frame_image_rect;
extern RECT g_frame_palette_rect;
extern RECT g_frame_palette_tail_rect;

extern u8* main_get_bin_as_tim(s32 lba, s32 byte_length);
extern void main_call_game_free(void* pointer);

void main_open_frame_bin_to_vram(void) {
    u8* frame = main_get_bin_as_tim(0xe68, 0x9800);

    LoadImage(&g_frame_image_rect, (u32*)(frame + 0x1000));
    LoadImage(&g_frame_palette_rect, (u32*)(frame + 0x9000));
    LoadImage(&g_frame_palette_tail_rect, (u32*)(frame + 0x9200));
    DrawSync(0);
    main_call_game_free(frame);
}
