#include "psx/types.h"

extern void process_event_commands(void);
extern s32 is_event_thread_running(s32 thread_id);

s32 battle_is_deployment_running(void) {
    process_event_commands();
    return is_event_thread_running(6);
}
