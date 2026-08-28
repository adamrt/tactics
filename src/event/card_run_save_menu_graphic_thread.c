#include "psx/pad.h"
#include "psx/types.h"

typedef struct CardInputDisplayState {
    void* render_otag;
    u32 display_value;
    u8 unknown_08[4];
    s16 scroll_x;
    u16 scroll_x_copy;
    u8 unknown_10[0x10];
    u16 unknown_20;
    u16 unknown_22;
} CardInputDisplayState;

extern s32 g_event_speed;
extern void* D_80166030;
extern u16 D_801ca870;
extern u16 D_801ca872;
extern CardInputDisplayState g_card_input_display_state;
extern void* g_card_render_otag;
extern u8 g_card_scaled_sprite_primitive_buffers[];

extern s32 battle_get_first_thread_parameter(void);
extern s32 battle_get_third_thread_parameter(void);
extern void switch_to_next_event_thread(void);
extern void stop_current_event_thread(void);
extern void card_build_scaled_sprite_primitive_chain(
    CardInputDisplayState* state, u8* input_state);

void card_run_save_menu_graphic_thread(void) {
    CardInputDisplayState* state;
    s32 frame;
    s32 button_mask;
    s32 mode;
    volatile u32 stack_padding[2];

    if (D_80166030 != 0) {
        g_card_input_display_state.unknown_20 = 0;
        mode = 8;
    } else {
        g_card_input_display_state.unknown_20 = 0x100;
        mode = 0x80;
    }
    g_card_input_display_state.unknown_22 = mode;

    button_mask = battle_get_first_thread_parameter();
    if (button_mask != 0) {
        button_mask = PSX_PAD_UP;
    } else {
        button_mask = PSX_PAD_RIGHT;
    }
    D_801ca870 = button_mask;
    D_801ca872 = button_mask;
    /* Fence: keeps the two D_801ca87x stores ahead of `frame = 0` /
     * `state = &g_card_input_display_state`; the scheduler otherwise interleaves them. */
    __asm__("" : : : "memory");

    frame = 0;
    state = &g_card_input_display_state;
    for (;;) {
        s32 loaded_scroll_x;
        s32 scroll_x;
        /* Pin + identity fence below: target reads scroll_x into $v0, stores
         * render_otag from $v1, then copies scroll_x to $v1 for the subtract.
         * Read-before-store and s16/u16/s32 copies all drop the copy. */
        register void* render_otag __asm__("$3") = g_card_render_otag;

        state->render_otag = render_otag;
        loaded_scroll_x = state->scroll_x;
        scroll_x = loaded_scroll_x;
        __asm__("" : "=r"(scroll_x) : "0"(scroll_x));
        if (loaded_scroll_x > 0x1000) {
            s32 delta = g_event_speed << 8;

            state->scroll_x = scroll_x - delta;
            state->scroll_x_copy -= delta;
        }
        state->display_value = 0x80;
        card_build_scaled_sprite_primitive_chain(
            state, g_card_scaled_sprite_primitive_buffers + ((frame & 1) * 0x4b0));
        switch_to_next_event_thread();
        if (battle_get_third_thread_parameter() != 0) {
            stop_current_event_thread();
        }
        frame++;
    }
}
