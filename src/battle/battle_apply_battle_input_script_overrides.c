#include "psx/types.h"

extern s32 battle_get_script_variable(s32 variable_id);
extern void main_game_reset(void);

void battle_apply_battle_input_script_overrides(u32* input) {
    u32 high_buttons;

    if (*input == 0x90c) {
        main_game_reset();
    }

    high_buttons = *input & 0xffff0000;
    *input &= battle_get_script_variable(0x29) ^ 0xffff;
    *input = high_buttons | (battle_get_script_variable(0x2a) | *input);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
