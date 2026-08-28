#include "psx/types.h"

extern s32 func_80133158(void);
extern s32 battle_check_thread_running_status(s32 index);
extern void switch_to_next_thread(void);

extern s32 g_battle_thread_records[16][256];

void battle_waitspritemove_event_instruction(void) {
    s32 target;
    s32 i;

    target = func_80133158();
    if (target == 2000) {
        return;
    }

    do {
        for (i = 0; i < 16; i++) {
            if (battle_check_thread_running_status(i) != 0) {
                if (g_battle_thread_records[i][0] == 11) {
                    if (g_battle_thread_records[i][1] == target) {
                        break;
                    }
                }
            }
        }
        if (i == 16) {
            return;
        }
        switch_to_next_thread();
    } while (1);
}
