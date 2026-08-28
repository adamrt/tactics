#include "psx/types.h"

extern s16 g_equip_sprite_ot_index;
extern s16 g_equip_semitransparency;
extern s32 D_801E9000;
extern u8 g_equip_zoom_draw_area_active;
extern u8* (*g_equip_sprite_command_handlers[])(void);

/* Dispatch every command of a sprite command stream through the opcode
   handler table until the 0x19 end-of-stream opcode. */
void equip_run_sprite_command_stream(u8* stream, s32 arg1) {
    g_equip_sprite_ot_index = 0;
    g_equip_semitransparency = 0;
    D_801E9000 = arg1;
    g_equip_zoom_draw_area_active = 0;
    if (stream[0] != 0x19) {
        do {
            stream = g_equip_sprite_command_handlers[stream[0]]();
        } while (stream[0] != 0x19);
    }
}
