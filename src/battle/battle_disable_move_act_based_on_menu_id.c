#include "psx/types.h"

extern s16 D_80166ADC;
extern s32 g_battle_current_menu_id;

s32 func_8014CBC0(void);
u8* battle_get_attacker_data_pointer(void);
void battle_set_sound_effect_to_invalid(void);
void func_8013B280(void);
void battle_stop_current_thread(void);
void battle_set_sound_effect_to_confirm_checked(void);
void func_801409A4(s32);

void battle_disable_move_act_based_on_menu_id(void) {
    s16* p;
    s32 id;
    s32 menu;

    id = func_8014CBC0();
    p = &D_80166ADC;
    *p = -2;
    if (battle_get_attacker_data_pointer()[0x5C] & 8) {
        *p = -1;
        battle_set_sound_effect_to_invalid();
        func_8013B280();
        battle_stop_current_thread();
    }
    menu = g_battle_current_menu_id;
    if (menu == 0xE || menu == 0x14 || menu == 0x21 || menu == 0x2F || menu == 0x31 || menu == 0x33) {
        battle_set_sound_effect_to_invalid();
        battle_stop_current_thread();
    }
    battle_set_sound_effect_to_confirm_checked();
    func_801409A4(id);
    battle_stop_current_thread();
}
