#include "psx/gpu.h"
#include "psx/types.h"

extern const u8* D_80173fec;
extern u32* g_battle_text_pointers[];
extern void* D_80173ff8;
extern u8 g_card_text_data[];
extern const u8 g_card_command_help_text[];
extern u16 g_card_save_menu_palette_image[0x100];
extern u8 g_card_save_menu_state;

extern void card_load_image_and_wait(RECT* rect, u32* data);
extern void card_store_image_and_wait(RECT* rect, u32* data);
extern void card_start_fade_from_0xf0(void);
extern void mark_thread_stopped(s32 thread_id);

void card_initialize_save_menu_graphics(void) {
    RECT rect;
    u16 image_data[16];

    D_80173ff8 = g_card_text_data;
    D_80173fec = g_card_command_help_text;

    rect.x = 0x100;
    rect.y = 0;
    rect.w = 0x40;
    rect.h = 0x30;
    card_load_image_and_wait(&rect, g_battle_text_pointers[0]);

    rect.x = 0x100;
    rect.y = 0xfa;
    rect.w = 0x40;
    rect.h = 4;
    card_load_image_and_wait(&rect, (u32*)g_card_save_menu_palette_image);

    rect.x = 0x3c0;
    rect.y = 0x1f0;
    rect.w = 0x10;
    rect.h = 1;
    card_store_image_and_wait(&rect, (u32*)image_data);
    image_data[4] = 0;

    rect.x = 0x120;
    rect.y = 0xfe;
    rect.w = 0x10;
    rect.h = 1;
    card_load_image_and_wait(&rect, (u32*)image_data);

    rect.x = 0x100;
    rect.y = 0xfe;
    rect.w = 0xc;
    rect.h = 1;
    card_load_image_and_wait(&rect, (u32*)&image_data[4]);

    rect.x = 0x3c0;
    rect.y = 0x1f4;
    rect.w = 0x10;
    rect.h = 1;
    card_store_image_and_wait(&rect, (u32*)image_data);
    image_data[4] = 0;

    rect.x = 0x130;
    rect.y = 0xfe;
    rect.w = 0x10;
    rect.h = 1;
    card_load_image_and_wait(&rect, (u32*)image_data);

    rect.x = 0x110;
    rect.y = 0xfe;
    rect.w = 0xc;
    rect.h = 1;
    card_load_image_and_wait(&rect, (u32*)&image_data[4]);

    card_start_fade_from_0xf0();
    g_card_save_menu_state = 0;
    mark_thread_stopped(15);
}
