#include "psx/types.h"

extern void func_801390BC(void);
extern void func_80139BEC(void);
extern void signal_menu_event_to_script(u32);

void battle_preview_ability_turn_at_list(void) {
    func_801390BC();
    signal_menu_event_to_script(0xFA);
    func_80139BEC();
}
