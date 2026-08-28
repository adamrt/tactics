#include "psx/types.h"

typedef struct OpenOpntexSequenceState {
    s32 fade_elapsed_frames;
    s32 fade_duration_frames;
    s32 fade_intensity;
    s32 first_frame;
    s32 last_frame;
    s32 frame_duration;
    s32 frame_countdown;
    s32 delay;
} OpenOpntexSequenceState;

extern OpenOpntexSequenceState g_open_opntex_sequence_state;
extern s32 g_open_opntex_first_frame;
extern s32 g_open_opntex_last_frame;
extern s32 g_open_opntex_frame_duration;
extern s32 g_open_opntex_frame_countdown;
extern s32 g_open_opntex_control_value;
extern s32 g_open_opntex_delay;
extern u32 g_open_script_dispatch_flags;
extern u8* g_open_opntex_data;

extern void open_put_opntex_in_frame_buffer(const void* source);

void open_update_opntex_sequence(void) {
    register volatile s32* duration_pointer __asm__("$4") = &g_open_opntex_sequence_state.frame_duration;
    register s32* countdown_pointer __asm__("$16");
    s32 delay;
    s32 countdown;
    s32 frame;
    volatile s32 outgoing_arguments[4];

    __asm__ volatile("" : "=r"(duration_pointer) : "0"(duration_pointer));
    if (*duration_pointer == 0) {
        return;
    }

    delay = g_open_opntex_delay;
    if (delay != 0) {
        delay--;
        g_open_opntex_delay = delay;
        if (delay == 0) {
            duration_pointer[-3] = 0x80;
            delay = duration_pointer[-0x5A6];
            frame = duration_pointer[3];
            duration_pointer[-5] = 0;
            duration_pointer[-0x5A6] = delay | 0x80;
            duration_pointer[-4] = frame;
        }
    }

    countdown_pointer = &g_open_opntex_frame_countdown;
    countdown = *countdown_pointer - 1;
    *countdown_pointer = countdown;
    if (countdown != 0) {
        return;
    }

    frame = g_open_opntex_first_frame;
    duration_pointer = (volatile s32*)(frame << 1);
    if (g_open_opntex_last_frame < frame) {
        g_open_opntex_frame_duration = 0;
        return;
    }

    __asm__ volatile(
        "addu $4,$4,$3\n"
        "sll $4,$4,3\n"
        "subu $4,$4,$3\n"
        "lui $2,0x8008\n"
        "lw $2,0x52a4($2)\n"
        "sll $4,$4,11\n"
        ".word 0x0c01a75f\n"
        "addu $4,$2,$4"
        :
        : "r"(duration_pointer), "r"(frame)
        : "$2", "$4", "$31", "memory");
    g_open_script_dispatch_flags |= 0x40;
    g_open_opntex_sequence_state.fade_elapsed_frames = 0;
    g_open_opntex_sequence_state.fade_intensity = 0;
    g_open_opntex_sequence_state.fade_duration_frames = g_open_opntex_control_value;
    g_open_opntex_first_frame++;
    *countdown_pointer = g_open_opntex_frame_duration;
    g_open_opntex_sequence_state.delay = g_open_opntex_frame_duration - g_open_opntex_control_value;
}
