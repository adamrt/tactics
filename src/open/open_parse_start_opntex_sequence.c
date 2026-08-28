#include "psx/types.h"

extern s32 g_open_opntex_first_frame;
extern s32 g_open_opntex_last_frame;
extern volatile s32 g_open_opntex_frame_duration;
extern volatile s32 g_open_opntex_frame_countdown;
extern volatile s32 g_open_opntex_control_value;
extern volatile s32 g_open_script_byte_offset;

void open_parse_start_opntex_sequence(const s16* command) {
    s32 final_value;
    s32 third_value;
    s32 active;
    s32 script_offset;

    command++;
    g_open_opntex_first_frame = *command++;
    g_open_opntex_last_frame = *command++;
    third_value = *command++;
    g_open_opntex_frame_duration = third_value;
    final_value = *command;
    script_offset = g_open_script_byte_offset;
    active = 1;
    g_open_opntex_frame_countdown = active;
    g_open_script_byte_offset = script_offset + 10;
    g_open_opntex_control_value = final_value;
}
