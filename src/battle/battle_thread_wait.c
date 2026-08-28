#include "psx/types.h"

extern void func_8014CA80(void);

void battle_thread_wait(s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_8014CA80();
    }
}
