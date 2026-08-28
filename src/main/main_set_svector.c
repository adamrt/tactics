#include "psx/gte.h"

void main_set_svector(SVECTOR* vector, s16 x, s16 y, s16 z) {
    vector->vx = x;
    vector->vy = y;
    vector->vz = z;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
