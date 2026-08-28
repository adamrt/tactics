#include "psx/gpu.h"
#include "psx/pad.h"
#include "psx/types.h"

typedef struct OptionScrollLayout {
    s16 step;
    s16 maximum;
} OptionScrollLayout;

extern u16 g_menu_input_disabled;
extern s32 g_menu_scroll_sound;
extern u8* g_event_threads;
extern s32 g_current_event_thread_id;
extern u8 g_option_menu_render_buffer[];

extern s32* battle_get_controller_input_pointer(s32 controller);
extern void clear_menu_render_buffer(void* buffer, s32 halfword_count);
extern void option_render_menu_entries(u8* menu, const s32* first_row,
    s32 render_context);
extern void world_copy_bytes(void* destination, const void* source, s32 count);

/* Apply scroll input, rebuild the menu image, and upload the changed region. */
void* option_update_menu_scroll_render(u8* menu, s32* first_row,
    s32* render_pending) {
    RECT source;
    RECT clear_strip;
    OptionScrollLayout* layout;
    s32* primary_input;
    s32* secondary_input;
    s32 changed;

    layout = *(OptionScrollLayout**)(menu + 0x30);
    primary_input = battle_get_controller_input_pointer(0);
    secondary_input = battle_get_controller_input_pointer(1);
    source.x = *(u16*)(menu + 0);
    source.y = *(u16*)(menu + 2);
    source.w = *(s16*)(menu + 4) >> 2;
    source.h = *(u16*)(menu + 6);
    changed = 0;

    if (g_menu_input_disabled != 0) {
        return 0;
    }

    if (((*secondary_input & 0x80) == 0) && (*(s32*)((g_current_event_thread_id << 10) + (s32)g_event_threads + 0x60) == 0)) {
        return 0;
    }

    if ((*primary_input & PSX_PAD_UP) != 0 && *first_row != 0) {
        *first_row -= layout->step;
        if (*first_row < 0) {
            *first_row = 0;
        }
        changed = 1;
        g_menu_scroll_sound = 3;
    } else if ((*primary_input & PSX_PAD_DOWN) != 0 && *first_row != layout->maximum) {
        *first_row += layout->step;
        if (*first_row > layout->maximum) {
            *first_row = layout->maximum;
        }
        changed = 1;
        g_menu_scroll_sound = 3;
    } else if (*(s32*)((g_current_event_thread_id << 10) + (s32)g_event_threads + 0x60) != 0) {
        changed = 1;
        *(s32*)((g_current_event_thread_id << 10) + (s32)g_event_threads + 0x60) = 0;
    }

    if (changed == 0) {
        return 0;
    }

    clear_menu_render_buffer(g_option_menu_render_buffer,
        (*(s16*)(menu + 4) * *(s16*)(menu + 6)) / 2);
    option_render_menu_entries(menu, first_row,
        (s32)g_option_menu_render_buffer);
    *render_pending = 0;
    LoadImage(&source, (u32*)g_option_menu_render_buffer);
    world_copy_bytes(&clear_strip, &source, sizeof(RECT));
    clear_strip.h = 2;
    clear_strip.x = source.x;
    clear_strip.y = ((source.y - 2) & 0xff) + (source.y & 0xff00);
    clear_strip.w = source.w;
    ClearImage(&clear_strip, 0, 0, 0);
    return g_option_menu_render_buffer;
}
