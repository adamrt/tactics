#include "psx/types.h"

extern void main_do_nothing(s32 a, s32 b);

void battle_noop_801a1328(void) {
    s32 unused[0x40];
    main_do_nothing(1, 0x320);
}
