#include "psx/types.h"

typedef struct {
    s16 a, b, c;
} TripleShort;

void battle_vector_mask_low_12_bits(TripleShort* src, TripleShort* dst) {
    dst->a = src->a & 0xFFF;
    dst->b = src->b & 0xFFF;
    dst->c = src->c & 0xFFF;
}
