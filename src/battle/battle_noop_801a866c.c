#include "psx/types.h"

extern void main_do_nothing(s32 category, s32 code);

void battle_noop_801a866c(void) {
    main_do_nothing(1, 0x50);
}
