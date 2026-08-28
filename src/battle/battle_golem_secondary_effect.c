#include "psx/types.h"

typedef struct SecondaryEffectData {
    u8 previous_target_id;
    u8 _pad001[2];
    u8 function_id;
    u8 _pad004[4];
    u32 state;   /* 0x08 */
    u16 counter; /* 0x0C */
    u8 _pad00e[0x1E];
    s16 h2c; /* 0x2C */
    s16 h2e; /* 0x2E */
    u8 _pad030[0x26];
} SecondaryEffectData;

typedef struct {
    s32 a, b, c;
} Triple;

extern SecondaryEffectData* g_current_secondary_effect;
extern u8 D_801B8846;

extern void func_801B0CF0(s32, s32);
extern void battle_save_effect_inertia_threshold(void);
extern void battle_set_effect_inertia_threshold(s32);
extern void battle_copy_on_hit_effects_data_to_second_section(void);
extern void battle_store_first_section_of_on_hit_effects_data(Triple* src);
extern void func_801B0F08(s32);
extern void battle_restore_effect_inertia_threshold(void);
extern void battle_copy_second_section_to_on_hit_effects_data(void);

s32 battle_golem_secondary_effect(void) {
    SecondaryEffectData* effect;
    SecondaryEffectData* e2;
    s32 unused[6];
    Triple pos;
    s32 result;
    s16 t;

    effect = g_current_secondary_effect;
    switch (effect->state) {
    case 1:
        result = 1;
        effect->h2c = 0;
        effect->counter = 0;
        effect->h2e = 0;
        effect->state = 2;
        break;
    case 2:
        func_801B0CF0(0x10, 0xD);
        /* fallthrough */
    case 3:
        battle_save_effect_inertia_threshold();
        battle_set_effect_inertia_threshold(0x230);
        pos.c = 0;
        pos.a = 0;
        pos.b = 0x1000;
        battle_copy_on_hit_effects_data_to_second_section();
        battle_store_first_section_of_on_hit_effects_data(&pos);
        func_801B0F08(0x10);
        battle_restore_effect_inertia_threshold();
        battle_copy_second_section_to_on_hit_effects_data();
        e2 = g_current_secondary_effect;
        t = e2->h2e;
        result = t != 1;
        e2->counter = e2->counter + 1;
        if (e2->h2c == 0 && (s16)e2->counter > (s32)D_801B8846) {
            e2->h2e = t + 1;
        }
        break;
    }
    return result;
}
