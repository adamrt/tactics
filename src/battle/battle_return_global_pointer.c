#include "psx/types.h"

void* battle_return_global_pointer(void) {
    void* gp;
    __asm__ volatile("move %0, $gp" : "=r"(gp));
    return gp;
}
