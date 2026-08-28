#include "psx/types.h"

extern s32 g_small_string_offsets[];
extern u8 g_small_string_data[];
extern u8* g_battle_text_pointers[32];

extern void set_script_variable(s32 variable_id, s32 value);

void battle_small_initialize_battle_text_pointers(void) {
    u8* string_data;

    string_data = g_small_string_data;
    g_battle_text_pointers[8] = string_data + g_small_string_offsets[0];
    g_battle_text_pointers[6] = string_data + g_small_string_offsets[1];
    g_battle_text_pointers[2] = g_battle_text_pointers[22];
    set_script_variable(0x39, 0);
}
