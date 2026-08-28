#include "fft/opening.h"

/* The birthday-menu controller's view of its open_controller_record_t. */
typedef struct OpenBirthdayMenuState {
    /* 0x00 */ s32 render_records[7];
    /* 0x1c */ s32 cursor;
    /* 0x20 */ s32 step;
} OpenBirthdayMenuState;

#define OPEN_BIRTHDAY_ENTRY_HIGHLIGHTED 9

extern s32 g_open_render_record_pointer_count;
extern volatile s32 g_open_new_button_presses;
extern u32 options[];

extern void open_hide_four_render_records(void* group);
extern void func_80017f6c(s32 value);
extern void main_play_sound(s32 id);
extern s32 open_check_repeating_directional_input(s32 mask);

void open_bin_0006b0a4_0006b354(OpenBirthdayMenuState* menu) {
    s32 record;

    if (menu->step == 2) {
        g_open_next_render_record_36 -= 3;
        g_open_render_record_pointer_count -= 3;
        g_open_current_controller_index -= 1;
        open_hide_four_render_records(&g_open_controller_records[g_open_current_controller_index]);
        /* The popped controller's own record, addressed from the pushed-record base. */
        g_open_controller_stream_start[g_open_current_controller_index - 1].field_14 = 0;
        return;
    }

    if (g_open_new_button_presses & 0x820) {
        func_80017f6c(menu->cursor);
        options[0] = (options[0] & 0xFF9FFFFF) | ((menu->cursor & 3) << 21);
        main_play_sound(1);
        menu->step = 2;
        return;
    }
    if (g_open_new_button_presses & 0x40) {
        main_play_sound(2);
        menu->step = 2;
        return;
    }

    if (open_check_repeating_directional_input(0x1000) != 0) {
        record = menu->render_records[menu->cursor];
        g_open_render_records_36[record].field_14 = 0;
        menu->cursor -= 1;
        if (menu->cursor < 0) {
            menu->cursor = 2;
        }
        record = menu->render_records[menu->cursor];
        g_open_render_records_36[record].field_14 = OPEN_BIRTHDAY_ENTRY_HIGHLIGHTED;
        main_play_sound(3);
    }

    if (open_check_repeating_directional_input(0x4000) != 0 || (g_open_new_button_presses & 0x100) != 0) {
        record = menu->render_records[menu->cursor];
        g_open_render_records_36[record].field_14 = 0;
        menu->cursor += 1;
        if (menu->cursor >= 3) {
            menu->cursor = 0;
        }
        record = menu->render_records[menu->cursor];
        g_open_render_records_36[record].field_14 = OPEN_BIRTHDAY_ENTRY_HIGHLIGHTED;
        main_play_sound(3);
    }
}
