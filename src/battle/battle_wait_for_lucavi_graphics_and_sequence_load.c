#include "psx/types.h"

extern s32 battle_load_lucavi_graphics_and_sequence(void);

void battle_wait_for_lucavi_graphics_and_sequence_load(void) {
    while (battle_load_lucavi_graphics_and_sequence() == 2) {
    }
}
