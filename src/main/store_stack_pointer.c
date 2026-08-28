#include "psx/types.h"

void store_stack_pointer(u32* destination) {
    register u32* output __asm__("$8") = destination;
    register u32 stack_pointer __asm__("$29");

    /* Preserve the retail register move and unscheduled return delay slot. */
    __asm__("" : : "r"(output));
    *output = stack_pointer;
    __asm__("");
}
