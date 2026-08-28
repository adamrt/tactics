#include "psx/types.h"

extern u8* g_battle_script_variables;

extern void battle_stop_current_thread(void);

s32* battle_get_variable_s_word_pointer_from_variable_s_id(s32 id) {
    s32* result;
    s32 off;

    if (id < 0x80) {
        result = (s32*)(id * 4 + (u32)g_battle_script_variables);
    } else if (id < 0x360) {
        off = ((id - 0x80) / 32) * 4 + 0x200;
        result = (s32*)(off + (u32)g_battle_script_variables);
    } else if (id < 0x400) {
        off = ((id - 0x360) / 8) * 4 + 0x25C;
        result = (s32*)(off + (u32)g_battle_script_variables);
    } else {
        battle_stop_current_thread();
    }
    return result;
}
