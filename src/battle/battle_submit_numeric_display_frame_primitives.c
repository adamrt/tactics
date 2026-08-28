#include "psx/types.h"

extern void submit_primitive(void* primitive);

/* Submit the twelve glyph packets and three framing packets. */
void battle_submit_numeric_display_frame_primitives(u8* display) {
    s32 index;
    s32 offset;

    index = 0;
    offset = 0x18;
    do {
        submit_primitive(display + offset);
        index++;
        offset += 0x10;
    } while (index < 12);
    submit_primitive(display);
    submit_primitive(display + 0xd8);
    submit_primitive(display + 0x0c);
}
