#include "psx/types.h"

extern void set_idle_animation(u8* unit);

void battle_call_set_animation_based_on_status(u8* unit) {
    set_idle_animation(unit);
}
