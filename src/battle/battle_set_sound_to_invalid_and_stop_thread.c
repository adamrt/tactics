#include "psx/types.h"

extern void battle_set_sound_effect_to_invalid(void);
extern void battle_stop_current_thread(void);

void battle_set_sound_to_invalid_and_stop_thread(void) {
    battle_set_sound_effect_to_invalid();
    battle_stop_current_thread();
}
