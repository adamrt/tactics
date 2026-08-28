#include "psx/types.h"

extern void equip_select_text_palette_and_metrics(s32 arg0);
extern void equip_run_sprite_command_stream(s32 arg0, s32 arg1);

void equip_dispatch_menu_with_override(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s0;

    var_s0 = arg1;
    if (arg2 != 0) {
        var_s0 = 0;
    }
    equip_select_text_palette_and_metrics(arg2);
    equip_run_sprite_command_stream(arg0, var_s0);
}
