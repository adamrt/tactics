#include "psx/types.h"

extern u8* g_open_opntex_data;
extern s32 g_open_script_byte_offset;
extern s32 g_open_script_fade_intensity;
extern void open_put_opntex_in_frame_buffer(const void* source);

/* Each OPNTEX frame occupies 23 * 0x800 bytes of the loaded data. */
#define OPEN_OPNTEX_FRAME_SECTORS 23

void open_parse_upload_opntex_frame(const s16* command) {
    s32 frame = command[1];
    s32 offset = frame * OPEN_OPNTEX_FRAME_SECTORS;
    u8* source;

    /* Zero-byte fence: the retail code loads the OPNTEX base after the frame
     * arithmetic and leaves the lh delay slot empty; without it GCC hoists
     * the load into that slot (a volatile read does not hold it back). */
    __asm__ volatile("");
    source = g_open_opntex_data;
    offset <<= 11;
    source += offset;
    open_put_opntex_in_frame_buffer(source);
    g_open_script_fade_intensity = 0;
    g_open_script_byte_offset += 4;
}
