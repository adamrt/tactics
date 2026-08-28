#include "psx/types.h"

/* Empty routine with two arguments; no callers remain in BATTLE.BIN. Both
 * parameters had their address taken by the (now dead) original body, which is
 * why they are still spilled to their incoming home slots. */
void battle_noop_801aad30(s32 arg0, s32 arg1) {
    s32* unused;
    unused = &arg0;
    unused = &arg1;
}
