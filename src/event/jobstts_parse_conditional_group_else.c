#include "psx/types.h"

typedef u8* (*JobsttsCommandFn)(u8*);
typedef s32 (*JobsttsConditionFn)(s32);

extern JobsttsCommandFn g_jobstts_render_command_handlers[];
extern JobsttsConditionFn g_jobstts_render_command_conditions[];
extern s16 g_jobstts_list_row_rendering;
extern s16 g_jobstts_list_scroll_offset_y;
extern s32 g_jobstts_list_row_index;
extern s16 g_jobstts_scroll_base_index;

u8* jobstts_parse_conditional_group_else(u8* data) {
    s32 then_count;
    s32 else_count;
    s32 arg;
    JobsttsConditionFn condition;

    then_count = data[4];
    else_count = data[5];
    condition = g_jobstts_render_command_conditions[data[3]];

    if (g_jobstts_list_row_rendering == 0) {
        arg = data[6];
    } else {
        arg = g_jobstts_scroll_base_index + g_jobstts_list_row_index;
        if (g_jobstts_list_scroll_offset_y < 0) {
            arg--;
        }
    }

    data += data[1];
    if (condition(arg)) {
        then_count -= 1;
        while (then_count != -1) {
            data = g_jobstts_render_command_handlers[data[0]](data);
            then_count -= 1;
        }
        else_count -= 1;
        while (else_count != -1) {
            data += data[1];
            else_count -= 1;
        }
    } else {
        then_count -= 1;
        while (then_count != -1) {
            data += data[1];
            then_count -= 1;
        }
        else_count -= 1;
        while (else_count != -1) {
            data = g_jobstts_render_command_handlers[data[0]](data);
            else_count -= 1;
        }
    }
    return data;
}
