#include "primitive_internal.h"

void SetSemiTrans(void* primitive, int enabled) {
    u8* bytes = (u8*)primitive;

    if (enabled != 0) {
        bytes[7] |= 2;
    } else {
        bytes[7] &= 0xfd;
    }
}
