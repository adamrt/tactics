#include "psx/types.h"

extern void* game_realloc(void*, u32);
extern void* g_high_overlay_load_address;
extern s32 g_font_print_enabled;
extern void FntPrint(const char* text);
extern void switch_to_next_thread(void);
extern const char D_8013D8A4[];

/* Retry the overlay allocation until it lands at the expected address, yielding and printing a debug message each pass. */
void battle_retry_alloc_with_message(u32 size) {
    while (1) {
        if (game_realloc(g_high_overlay_load_address, size) == g_high_overlay_load_address) {
            break;
        }
        switch_to_next_thread();
        if (g_font_print_enabled != 0) {
            FntPrint(D_8013D8A4);
        }
    }
}
