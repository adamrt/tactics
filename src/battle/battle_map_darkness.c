#include "psx/types.h"

extern void battle_set_thread_task_id(s32);
extern void battle_stop_current_thread(void);
extern void battle_thread_wait(s32);
extern void* func_8014CBC0(void);
extern void battle_set_map_darkness(s32 mode, s32 frame_duration, s16 red, s16 green, s16 blue);
extern u16 D_80169700[];

void battle_map_darkness(void) {
    u8* r;

    battle_set_thread_task_id(6);
    r = func_8014CBC0();
    battle_set_map_darkness(r[0], r[4], (s8)r[1], (s8)r[2], (s8)r[3]);
    battle_thread_wait(D_80169700[r[4]]);
    battle_stop_current_thread();
}
