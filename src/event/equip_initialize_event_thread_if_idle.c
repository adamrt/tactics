#include "psx/types.h"

extern s32 is_event_thread_running(void);
extern void initialize_event_thread(s32, void*);
extern void battle_store_thread_function_parameters(s32, s32, s32, s32);
extern void text_character_handling_thread(void);

void equip_initialize_event_thread_if_idle(s32 a, s32 b, s32 c, s32 d) {
    if (is_event_thread_running() == 0) {
        initialize_event_thread(a, text_character_handling_thread);
        battle_store_thread_function_parameters(a, b, c, d);
    }
}
