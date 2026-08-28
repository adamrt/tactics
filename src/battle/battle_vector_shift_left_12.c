#include "psx/types.h"

typedef struct {
    s32 a, b, c;
} Triple;

void battle_vector_shift_left_12(Triple* src, Triple* dst) {
    dst->a = src->a << 12;
    dst->b = src->b << 12;
    dst->c = src->c << 12;
}
