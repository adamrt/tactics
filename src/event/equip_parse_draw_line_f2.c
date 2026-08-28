#include "psx/types.h"

extern u8 g_equip_semitransparency;
extern s16 g_equip_sprite_ot_index;
extern void equip_enqueue_line_f2(s16* endpoints, u8* color, s32 semi, s32 ot);

/* EQUIP.OUT 001caf14 - Stream command: draw a LINE_F2 from (x0, y0) to
   (x1, y1) with the RGB that follows the endpoints in the command. */
u8* equip_parse_draw_line_f2(u8* stream) {
    s16 endpoints[4];

    endpoints[0] = stream[2];
    endpoints[1] = stream[3];
    endpoints[2] = stream[4];
    endpoints[3] = stream[5];
    equip_enqueue_line_f2(endpoints, stream + 6, g_equip_semitransparency, g_equip_sprite_ot_index);
    return stream + stream[1];
}
