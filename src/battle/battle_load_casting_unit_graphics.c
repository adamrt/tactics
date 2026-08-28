#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void battle_load_unit_graphics_info(battle_misc_data_t* unit, u8* sprite_data,
    u32 shape_frame,
    u32 current_animation);

void battle_load_casting_unit_graphics(void) {
    battle_misc_data_t* unit;

    unit = battle_get_casting_unit_misc_data();
    if (unit != 0) {
        /* The sprite data block starts at the graphic trigger; 0x1e0 is the
         * current frame (wiki). */
        battle_load_unit_graphics_info(unit, (u8*)&unit->sprite_graphic_trigger,
            *(u16*)&unit->_unknown_1de[2],
            unit->encoded_animation);
    }
}
