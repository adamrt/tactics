#include "psx/types.h"

/* Copy a byte range used by WORLD.BIN data setup. */
void world_copy_bytes(u8* destination, const u8* source, s32 count) {
    register u8 value __asm__("$7");

    /* Hand-assembled in the retail binary: trapping addi updates, a nop after
     * the lbu and an unfilled bnez delay slot. GCC emits addiu and fills both. */
    do {
        value = *source;
        *destination = value;
        __asm__ volatile("addi %0,%0,1" : "=r"(destination) : "0"(destination));
        __asm__ volatile("addi %0,%0,1" : "=r"(source) : "0"(source));
        __asm__ volatile("addi %0,%0,-1" : "=r"(count) : "0"(count));
    } while (count);
}
