#include "psx/types.h"

typedef struct {
    s32 a, b, c;
} Triple;
extern Triple on_hit_effects_data;

void battle_store_first_section_of_on_hit_effects_data(Triple* src) {
    on_hit_effects_data = *src;
}
