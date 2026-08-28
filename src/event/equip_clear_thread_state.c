#include "psx/types.h"

extern s32 g_equip_thread_state;
extern void equip_set_thread_completion_parameters(s32 id);

void equip_clear_thread_state(s32 id) {
    equip_set_thread_completion_parameters(id);
    g_equip_thread_state = 0;
}
