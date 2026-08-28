#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u16 misc_id);
extern void battle_append_unit_graphics_load_descriptor(s32 map_x, s32 map_y,
    s32 map_level, s16 map_height,
    s16 portrait_id,
    s32 palette_id, s16 misc_id,
    s32 battle_stats, s32 flags);

extern s32 D_80049C18;
extern s32 D_80098D74;
extern s32 D_80098D78;
extern s32 D_80098D7C;
extern s32 D_80098D80;

s32 battle_event_instruction_add_ghost_unit(s32 map_x, s32 map_y, s32 map_level,
    u16 map_height, s32 portrait_id,
    s32 misc_id, s32 flags) {
    s32 ret;

    if (battle_get_unit_misc_data_by_misc_id(misc_id) != 0) {
        ret = 0;
        goto done;
    }
    D_80049C18 = 0;
    D_80098D74 = 0;
    D_80098D78 = 0;
    D_80098D7C = 0;
    D_80098D80 = 0;
    battle_append_unit_graphics_load_descriptor(map_x, map_y, map_level, map_height,
        portrait_id, 0, misc_id, 0, flags);
    ret = 1;
done:
    return ret;
}
