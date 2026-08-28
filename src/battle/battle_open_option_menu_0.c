#include "psx/types.h"

extern void battle_set_option_menu_open(void);
extern void battle_setup_open_companion_executable(s32 id);
extern void func_801C1A3C(s32 arg0);

void battle_open_option_menu_0(void) {
    battle_set_option_menu_open();
    battle_setup_open_companion_executable(1);
    func_801C1A3C(0);
}
