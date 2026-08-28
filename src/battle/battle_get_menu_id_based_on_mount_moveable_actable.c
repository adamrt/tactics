#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* battle_get_existent_battle_unit_pointer(s32 unit_id);
extern s32 func_801811F8(battle_stats_t* unit);

s32 battle_get_menu_id_based_on_mount_moveable_actable(s32 unit_id) {
    battle_stats_t* unit;
    s32 menu;

    unit = battle_get_existent_battle_unit_pointer(unit_id);
    if (unit == 0) {
        return -1;
    }
    menu = func_801811F8(unit);
    if ((unit->mount_info & 0x80) != 0) {
        switch (menu) {
        case 0x0:
            menu = 0x2e;
            break;
        case 0xe:
            menu = 0x2f;
            break;
        case 0x13:
            menu = 0x30;
            break;
        case 0x14:
            menu = 0x31;
            break;
        default:
            return menu;
        }
    }
    return menu;
}
