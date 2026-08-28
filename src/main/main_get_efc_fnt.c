#include "psx/etc.h"
#include "psx/gpu.h"

/* Low immediate byte of FntLoad's CLUT-Y addiu instruction. */
extern volatile u8 g_fntload_clut_y_offset_immediate;
extern u8 g_cd_file_state;

extern void* main_get_bin_as_tim(u32, u32);
extern void free_loaded_file(void*);
extern void open_file_to_ram_center(void*);

void main_get_efc_fnt(void) {
    TIM_IMAGE image;
    void* data;
    int loaded = 0;

    g_fntload_clut_y_offset_immediate = 0x7f;
    FntLoad(0x280, 0);

    while (!loaded) {
        data = main_get_bin_as_tim(0xdea8, 0x8800);
        if (data != 0) {
            if (OpenTIM(data) == 0 && ReadTIM(&image) != 0) {
                LoadTPage(image.paddr, 0, 0, 0x280, 0, image.prect->w * 4, image.prect->h);
                loaded = 1;
                LoadClut2(image.caddr, 0x280, 0x7f);
            }
            free_loaded_file(data);
        } else {
            VSync(0);
            open_file_to_ram_center(&g_cd_file_state);
        }
    }

    SetDumpFnt(FntOpen(0x88, 0x10, 0x100, 0x100, 0, 0x200));
    DrawSync(0);
    DrawSync(0);
}
