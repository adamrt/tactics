#include "psx/types.h"

typedef s32 (*JobsttsPredicate)(s32);
typedef u8* (*JobsttsHandler)(u8*);

extern s16 g_jobstts_list_row_rendering;
extern s16 g_jobstts_scroll_base_index;
extern s32 g_jobstts_list_row_index;
extern s16 g_jobstts_list_scroll_offset_y;
extern JobsttsPredicate g_jobstts_render_command_conditions[];
extern JobsttsHandler g_jobstts_render_command_handlers[];

u8* jobstts_parse_conditional_group(u8* data) {
    s32 count;
    JobsttsPredicate condition;
    s32 index;

    count = data[4];
    condition = g_jobstts_render_command_conditions[data[3]];
    if (g_jobstts_list_row_rendering == 0) {
        index = data[5];
    } else {
        index = g_jobstts_scroll_base_index + g_jobstts_list_row_index;
        if (g_jobstts_list_scroll_offset_y < 0) {
            index -= 1;
        }
    }
    data += data[1];
    if (condition(index) == 0) {
        count -= 1;
        while (count != -1) {
            data += data[1];
            count -= 1;
        }
        return data;
    }
    count -= 1;
    while (count != -1) {
        data = g_jobstts_render_command_handlers[data[0]](data);
        count -= 1;
    }
    return data;
}
