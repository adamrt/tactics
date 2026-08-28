#include "primitive_internal.h"

void SetDrawMove(void* primitive) {
    u8* bytes = (u8*)primitive;

    bytes[3] = 5;
    bytes[7] = 1;
    *(u32*)(bytes + 8) = 0x80000000;
}
