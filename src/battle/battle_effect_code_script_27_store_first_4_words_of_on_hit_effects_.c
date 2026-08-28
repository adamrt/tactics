#include "psx/types.h"

typedef struct {
    s32 a, b, c;
} Triple;
extern void battle_store_first_section_of_on_hit_effects_data(Triple* src);
extern void battle_set_effect_inertia_threshold(s32 arg0);
extern u8* g_effect_particle_system_data;

s32 battle_effect_code_script_27_store_first_4_words_of_on_hit_effects_(u16* ctx) {
    battle_store_first_section_of_on_hit_effects_data((Triple*)(g_effect_particle_system_data + 4));
    battle_set_effect_inertia_threshold(*(s32*)(g_effect_particle_system_data + 0x10));
    ctx[3] += 2;
    return 1;
}
