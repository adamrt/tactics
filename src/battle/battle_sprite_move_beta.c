#include "psx/types.h"

extern void battle_set_thread_task_id(s32 task_id);
extern s32 battle_get_first_thread_parameter(void);
extern void func_80146940(s32 arg0, s32 arg1);
extern void battle_stop_current_thread(void);

void battle_sprite_move_beta(void) {
    battle_set_thread_task_id(0xB);
    func_80146940(battle_get_first_thread_parameter(), 1);
    battle_stop_current_thread();
}
