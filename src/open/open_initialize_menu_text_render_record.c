#include "fft/opening.h"

typedef struct OpenPackedHalfwordPair {
    u16 first;
    u16 second;
} OpenPackedHalfwordPair;

void open_bin_0006c750_0006c8a4(s32 record_index, OpenPackedHalfwordPair first_pair,
    OpenPackedHalfwordPair second_pair, s32 parameter,
    void* image);
void open_display_birthday_menu_text_entry(s32 record_index,
    s32 combined_text_index, s32 x,
    s32 y, void* image);
void open_upload_birthday_window_image(s32 record_index, void* image);

#define OPEN_MENU_TEXT_MARGIN 8

void open_initialize_menu_text_render_record(
    s32 record_index, OpenPackedHalfwordPair first_pair,
    OpenPackedHalfwordPair second_pair, s32 parameter, s32 combined_text_index,
    void* image) {
    /* A struct keeps the two values stack-resident (0x18 / 0x1c) and still
     * lets the y store fill the beqz delay slot; volatile would not. */
    struct {
        s32 x;
        s32 y;
    } text;
    s32 margin;

    open_bin_0006c750_0006c8a4(record_index, first_pair, second_pair, parameter, image);

    margin = OPEN_MENU_TEXT_MARGIN;
    text.x = margin;
    text.y = margin;
    if (combined_text_index != 0) {
        open_display_birthday_menu_text_entry(
            record_index, combined_text_index, text.x, text.y, image);
    }
    open_upload_birthday_window_image(record_index, image);
    g_open_render_records_56[record_index].flags |= 0x100;
}
