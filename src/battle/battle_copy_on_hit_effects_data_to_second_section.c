#include "psx/types.h"

typedef struct {
    s32 a, b, c;
} Triple;

extern Triple on_hit_effects_data;
extern Triple on_hit_effects_data_second_section;

void battle_copy_on_hit_effects_data_to_second_section(void) {
    on_hit_effects_data_second_section = on_hit_effects_data;
}
