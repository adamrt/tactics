#include "psx/types.h"

extern void main_do_nothing(s32, s32);

/* Effect-table no-op callback; the zero return selects the normal path. */
s32 battle_effect_noop_return_zero(void) {
    main_do_nothing(1, 0x320);
    return 0;
}
