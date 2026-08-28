#include "fft/battle.h"

extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(s32 misc_id);
extern void battle_palette_modification(
    s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h);

void battle_highlight_all_units_blue_or_red(s32 mode) {
    battle_misc_data_t* caster;
    battle_misc_data_t* unit;
    s32 i;

    caster = battle_get_casting_unit_misc_data();
    for (i = 0; i < 0x10; i++) {
        unit = battle_get_unit_misc_data_by_misc_id(i & 0xFFFF);
        if (unit == 0) {
            continue;
        }
        if (unit->battle_data == 0) {
            continue;
        }
        switch (mode) {
        case 0xC:
            if ((unit->battle_data->team_flags & BATTLE_TEAM_MASK) != (caster->battle_data->team_flags & BATTLE_TEAM_MASK)) {
                battle_palette_modification(9, 4, 3, i, 0, 0x10, 0, 0);
            }
            continue;
        case 0xE:
            if ((unit->battle_data->team_flags & BATTLE_TEAM_MASK) == (caster->battle_data->team_flags & BATTLE_TEAM_MASK)) {
                battle_palette_modification(9, 4, 3, i, 0, 0, 0, 0x18);
            }
            continue;
        }
    }
}
