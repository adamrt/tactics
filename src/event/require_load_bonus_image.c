#include "psx/types.h"

extern void* g_high_overlay_load_address;
extern s32 (*g_call_inner_subroutine_target)();
extern const s16 g_require_bonus_image_rect[];
extern const s16 g_require_bonus_palette_rect[];

extern void switch_to_next_thread(void);
extern void* game_realloc(void* allocation, u32 size);
extern s32 main_call_build_file_header(s32 lba, s32 size, void* destination);
extern s32 call_inner_subroutine();
extern s32 main_check_file_still_loading(void);
extern void LoadImage(const s16* rectangle, const void* pixels);
extern void main_game_free(void* allocation);

void require_load_bonus_image(s32 image_id) {
    void* allocation;
    register s32 selected_image __asm__("$17") = image_id;
    s32 (*build_operation)();

    do {
        switch_to_next_thread();
        allocation = game_realloc(g_high_overlay_load_address, 0x8000);
    } while (allocation != g_high_overlay_load_address);

    build_operation = main_call_build_file_header;
    selected_image *= 13;
    do {
        switch_to_next_thread();
        g_call_inner_subroutine_target = build_operation;
    } while (call_inner_subroutine(selected_image + 0x16c0, 0x6800,
                 allocation)
        != 0);

    {
        s32 (*poll_operation)() = main_check_file_still_loading;
        do {
            switch_to_next_thread();
            g_call_inner_subroutine_target = poll_operation;
        } while (call_inner_subroutine() != 0);
    }

    LoadImage(g_require_bonus_image_rect, allocation);
    LoadImage(g_require_bonus_palette_rect, (u8*)allocation + 0x6400);
    switch_to_next_thread();
    main_game_free(allocation);
}
