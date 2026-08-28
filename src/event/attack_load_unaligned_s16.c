#include "psx/types.h"

s16 attack_load_unaligned_s16(const u8* ptr) {
    return (ptr[1] << 8) | ptr[0];
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
