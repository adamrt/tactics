#include "psx/types.h"

extern s32 battle_get_thread_running_task(s32);
extern void battle_set_sound_effect_to_confirm(void);
extern void battle_retry_alloc_with_message(s32);
extern void battle_setup_open_companion_executable(s32);
extern void func_801DF050(void);

void battle_menu_building_thread(void) {
    if (battle_get_thread_running_task(0x15) != 0 && battle_get_thread_running_task(0x31) == 0) {
        battle_set_sound_effect_to_confirm();
    }
    battle_retry_alloc_with_message(0x20000);
    battle_setup_open_companion_executable(3);
    func_801DF050();
}
