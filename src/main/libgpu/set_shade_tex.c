#include "primitive_internal.h"

void SetShadeTex(void* primitive, int enabled) {
    u8* bytes = (u8*)primitive;

    if (enabled != 0) {
        bytes[7] |= 1;
    } else {
        bytes[7] &= 0xfe;
    }
}
