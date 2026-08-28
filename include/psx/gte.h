#ifndef FFT_PSX_GTE_H
#define FFT_PSX_GTE_H

#include "types.h"

typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SVECTOR;

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
    s32 pad;
} VECTOR;

typedef char assert_svector_size[sizeof(SVECTOR) == 8 ? 1 : -1];
typedef char assert_vector_size[sizeof(VECTOR) == 16 ? 1 : -1];

extern void SetGeomOffset(int, int);
extern void SetGeomScreen(int);
extern void InitGeom(void);

#endif
