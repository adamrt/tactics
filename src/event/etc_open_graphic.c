#include "psx/types.h"

typedef struct EtcGraphic {
    const char* path;
    s32 lba;
    s32 size;
    void* framebuffer_rect;
    s16* dimensions;
    void* unused_14;
    void* unused_18;
    s32 texture_mode;
} EtcGraphic;

typedef struct EventThread {
    u8 reserved_00[0xc];
    s32 yield_state;
    u8 reserved_10[0x3f0];
} EventThread;

extern u8* g_high_overlay_load_address;
extern s32 g_font_print_enabled;
extern const char g_etc_allocation_wait_message[];
extern EtcGraphic g_etc_graphics[];
extern s32 g_etc_game_over_palette_rect;
extern s16 g_etc_graphics_enabled;
extern s32 g_etc_screen_fade;
extern EventThread* g_event_threads;
extern s32 g_current_event_thread_id;
extern s32 (*g_call_inner_subroutine_target)();
extern s32 main_load_data_from_disc(s32 lba, s32 size, void* destination);
extern s32 main_check_file_still_loading(void);

extern u8* game_realloc(void* start, s32 size);
extern void main_game_free(void* allocation);
extern s32 call_inner_subroutine();
extern void switch_to_next_thread(void);
extern void FntPrint(const char* text);
extern s32 LoadImage(void* rect, void* data);
extern s32 DrawSync(s32 mode);

void etc_open_graphic(s32 graphic_id) {
    u8* image_buffer;
    s32 count;

    while (1) {
        image_buffer = game_realloc(g_high_overlay_load_address, 0x20000);
        if (image_buffer == g_high_overlay_load_address) {
            break;
        }
        switch_to_next_thread();
        if (g_font_print_enabled != 0) {
            FntPrint(g_etc_allocation_wait_message);
        }
    }

    do {
        switch_to_next_thread();
        g_call_inner_subroutine_target = main_load_data_from_disc;
    } while (call_inner_subroutine(
                 g_etc_graphics[graphic_id].lba,
                 g_etc_graphics[graphic_id].size,
                 image_buffer)
        != 0);
    do {
        switch_to_next_thread();
        g_call_inner_subroutine_target = main_check_file_still_loading;
    } while (call_inner_subroutine() != 0);

    if ((u32)g_etc_graphics[graphic_id].texture_mode < 2U) {
        LoadImage(g_etc_graphics[graphic_id].framebuffer_rect, image_buffer);
        if (g_etc_graphics[graphic_id].texture_mode == 1) {
            LoadImage(&g_etc_game_over_palette_rect,
                image_buffer + g_etc_graphics[graphic_id].size - 0x200);
        }
    } else {
        g_etc_graphics_enabled = 1;
        if (graphic_id == 8) {
            g_etc_screen_fade = -0xff;
            do {
                switch_to_next_thread();
                g_etc_screen_fade += 8;
            } while (g_etc_screen_fade <= 0);
        } else {
            g_etc_screen_fade = 0xff;
            do {
                switch_to_next_thread();
                g_etc_screen_fade -= 8;
            } while (g_etc_screen_fade > 0);
        }
        g_etc_screen_fade = 0;

        if (graphic_id == 8) {
            count = 0;
            do {
                count++;
                switch_to_next_thread();
                g_event_threads[g_current_event_thread_id].yield_state = 1;
            } while (count < 0x4ec);
        } else if (graphic_id == 10) {
            count = 0;
            do {
                count++;
                switch_to_next_thread();
                g_event_threads[g_current_event_thread_id].yield_state = 1;
            } while (count < 0x5a0);
        } else if (graphic_id == 11) {
            count = 0;
            do {
                count++;
                switch_to_next_thread();
                g_event_threads[g_current_event_thread_id].yield_state = 1;
            } while (count < 0x8ac);
        } else {
            count = 0;
            if (graphic_id == 12) {
                do {
                    count++;
                    switch_to_next_thread();
                    g_event_threads[g_current_event_thread_id].yield_state = 1;
                } while (count < 0x258);
            } else {
                do {
                    count++;
                    switch_to_next_thread();
                    g_event_threads[g_current_event_thread_id].yield_state = 1;
                } while (count < 0x17e8);
            }
        }

        g_etc_screen_fade = 0;
        do {
            switch_to_next_thread();
            switch_to_next_thread();
            g_etc_screen_fade += 8;
        } while (g_etc_screen_fade < 0x100);
        g_etc_screen_fade = 0xff;
        g_etc_graphics_enabled = 0;
        if (graphic_id == 10) {
            g_etc_screen_fade = 0;
        }
    }

    DrawSync(0);
    main_game_free(image_buffer);
}
