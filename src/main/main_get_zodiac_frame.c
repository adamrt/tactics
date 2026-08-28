#include "psx/gpu.h"

extern u32* main_get_bin_as_tim(int, int);
extern void main_game_free(void*);
extern void main_open_frame_bin_to_vram(void);

void main_get_zodiac_frame(void) {
    RECT destination = { 640, 0, 128, 256 };
    u32* image;

    image = main_get_bin_as_tim(0xec61, 0x10000);
    LoadImage(&destination, image);
    DrawSync(0);
    main_game_free(image);
    main_open_frame_bin_to_vram();
}
