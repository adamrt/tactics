#ifndef FFT_OPENING_H
#define FFT_OPENING_H

#include "psx/gpu.h"
#include "psx/types.h"

/* Shared VLC/MDEC state used by OPEN.BIN's movie-stream pipeline. */
typedef struct open_mdec_stream_state {
    void* vlc_buffers[2];    /* 0x00 */
    s32 vlc_buffer_index;    /* 0x08 */
    void* output_buffers[2]; /* 0x0c */
    s32 output_buffer_index; /* 0x14 */
    RECT frame_rects[2];     /* 0x18 */
    s32 frame_rect_index;    /* 0x28 */
    RECT output_rect;        /* 0x2c */
    s32 output_ready;        /* 0x34 */
} open_mdec_stream_state_t;

typedef char OpenMdecStreamState_size_must_be_0x38[(sizeof(open_mdec_stream_state_t) == 0x38) ? 1 : -1];

extern open_mdec_stream_state_t g_open_mdec_stream_state;

/* One 100-byte state record per controller. The current controller c runs
 * g_open_controller_handlers[g_open_controller_handler_indices[c - 1]] on
 * g_open_controller_records[c]. A push made while the current index is c
 * fills g_open_controller_stream_start[c] (which is records[c + 1]) and
 * stores the new handler id at handler_indices[c]. Only the stream pair is
 * common; the remaining words are handler-specific (the thread-2 controller
 * keeps run_followup / result in the first two words). */
typedef struct open_controller_record {
    /* 0x00 */ s32 stream_start;
    /* 0x04 */ s32 stream_length;
    /* 0x08 */ s32 field_08;
    /* 0x0c */ s32 field_0c;
    /* 0x10 */ s32 field_10;
    /* 0x14 */ s32 field_14;
    /* 0x18 */ u8 padding_18[0x64 - 0x18];
} open_controller_record_t;

typedef char OpenControllerRecord_size_must_be_0x64[(sizeof(open_controller_record_t) == 0x64) ? 1 : -1];

/* Render records. open_render_record_pointer_list dispatches on flags bit 0
 * (36-byte record) or bit 1 (56-byte record); bit 4 marks a visible record.
 * Both pools hold 16 entries, allocated by the open_append_render_record_*
 * counters. */
typedef struct open_render_record_36 {
    /* 0x00 */ u32 flags;
    /* 0x04 */ s32 field_04;
    /* 0x08 */ s32 field_08;
    /* 0x0c */ s32 field_0c;
    /* 0x10 */ s32 field_10;
    /* 0x14 */ s32 field_14; /* birthday menu: 9 = highlighted entry */
    /* 0x18 */ s32 field_18;
    /* 0x1c */ s32 field_1c;
    /* 0x20 */ u8 r;
    /* 0x21 */ u8 g;
    /* 0x22 */ u8 b;
    /* 0x23 */ u8 padding_23;
} open_render_record_36_t;

/* The last 20 bytes of a 56-byte record; the retail code addresses them
 * through a separate base (g_open_quad_records == &records_56[0].tail). */
typedef struct open_render_record_56_tail {
    /* 0x00 */ s32 field_24;
    /* 0x04 */ s32 field_28;
    /* 0x08 */ RECT quad; /* quarter-pixel source rectangle */
    /* 0x10 */ u8 r;
    /* 0x11 */ u8 g;
    /* 0x12 */ u8 b;
    /* 0x13 */ u8 padding_13;
} open_render_record_56_tail_t;

typedef struct open_render_record_56 {
    /* 0x00 */ u32 flags;
    /* 0x04 */ s32 vram_x; /* quad.x / 4 + 64 * depth + 0x180 */
    /* 0x08 */ s32 vram_y;
    /* 0x0c */ s32 field_0c;
    /* 0x10 */ s32 depth;
    /* 0x14 */ s32 field_14;
    /* 0x18 */ s32 field_18;
    /* 0x1c */ s32 x; /* quad.x - 0x80 */
    /* 0x20 */ s32 y; /* quad.y - 0x78 */
    /* 0x24 */ open_render_record_56_tail_t tail;
} open_render_record_56_t;

typedef char OpenRenderRecord36_size_must_be_0x24[(sizeof(open_render_record_36_t) == 0x24) ? 1 : -1];
typedef char OpenRenderRecord56_size_must_be_0x38[(sizeof(open_render_record_56_t) == 0x38) ? 1 : -1];

#define OPEN_RENDER_RECORD_VISIBLE 0x10

extern open_render_record_36_t g_open_render_records_36[16];
extern open_render_record_56_t g_open_render_records_56[16];
extern s32 g_open_next_render_record_36;
extern s32 g_open_next_render_record_56;

typedef void (*open_controller_handler_t)(void* record);

extern open_controller_record_t g_open_controller_records[];
extern open_controller_record_t g_open_controller_stream_start[];
extern s32 g_open_current_controller_index;
extern s32 g_open_controller_handler_indices[];
extern open_controller_handler_t g_open_controller_handlers[];

#endif
