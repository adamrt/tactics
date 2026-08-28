#include "fft/opening.h"

/* The title-exit controller's view of its open_controller_record_t. */
typedef struct OpenTitleExitState {
    s32 state;
} OpenTitleExitState;

extern u32 g_open_overlay_fade_flags;
extern s32 g_open_render_record_pointer_count;
extern u32 g_open_runtime_flags;
extern u32 g_open_new_button_presses;
extern s32* g_open_file_destination;
extern s32 g_open_work_buffer_0[];

extern void SetDispMask(s32 enabled);
extern void main_play_sound(s32 sound_id);
extern void open_start_overlay_fade_in(s32 speed);
extern void func_8006A174(s32 argument);
extern void open_begin_new_game_transition(void);

void open_update_title_exit_transition(OpenTitleExitState* transition) {
    s32 state;

    if ((g_open_overlay_fade_flags & 4) != 0) {
        return;
    }

    if (transition->state != 0) {
        g_open_next_render_record_36 -= 1;
        g_open_render_record_pointer_count -= 1;
        g_open_current_controller_index -= 1;
        state = transition->state;
        if (state == 1) {
            s32* source;
            s32* destination;
            s32 index;

            SetDispMask(0);
            index = 0;
            source = g_open_work_buffer_0;
            g_open_runtime_flags |= 0x40;
            destination = g_open_file_destination;
            do {
                *destination = *source;
                source++;
                index++;
                destination++;
            } while (index < 0x7800);
            func_8006A174(0);
        } else if (state == 2) {
            open_begin_new_game_transition();
        }
        return;
    }

    if ((g_open_new_button_presses & 0x40) != 0) {
        main_play_sound(2);
        open_start_overlay_fade_in(0x20);
        transition->state = 1;
    } else if ((g_open_new_button_presses & 0x820) != 0) {
        main_play_sound(1);
        open_start_overlay_fade_in(0x20);
        transition->state = 2;
    }
}
