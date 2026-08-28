#include "psx/types.h"

extern s32 g_current_event_thread_id;

typedef struct {
    s32 task_id;
    char pad[0x3fc];
} BattleThreadRec;
extern BattleThreadRec g_battle_thread_records[];

void battle_set_thread_task_id(s32 task_id) {
    g_battle_thread_records[g_current_event_thread_id].task_id = task_id;
}
