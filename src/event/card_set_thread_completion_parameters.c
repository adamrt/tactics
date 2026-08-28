#include "psx/types.h"

extern void battle_store_thread_function_parameters(s32 id, s32 value0, s32 value1,
    s32 value2);

void card_set_thread_completion_parameters(s32 id) {
    battle_store_thread_function_parameters(id, 0, 0, 1);
}
