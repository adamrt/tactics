#include "psx/types.h"

extern void battle_apply_battle_input_script_overrides(u32* input);

extern u32 g_unfiltered_battle_controller_input;

void battle_filter_battle_controller_input(u32* input) {
    g_unfiltered_battle_controller_input = *input;
    battle_apply_battle_input_script_overrides(input);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
