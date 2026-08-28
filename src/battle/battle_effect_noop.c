#include "psx/types.h"

extern void main_do_nothing(s32, s32);

/* Effect-table no-op callback used where no effect-side action is needed. */
void battle_effect_noop(void) {
    main_do_nothing(1, 0x320);
}
