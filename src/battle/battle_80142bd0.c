#include "psx/types.h"

extern u16 g_menu_input_disabled;
extern void battle_set_script_variable(s32 id, s32 value);
extern void func_8014CA80(void);

void battle_80142bd0(s32 arg0) {
    if (g_menu_input_disabled == 2) {
        battle_set_script_variable(0x56, arg0);
        battle_set_script_variable(0x29, 0xFFFF);
        func_8014CA80();
        battle_set_script_variable(0x56, 0);
    }
}
