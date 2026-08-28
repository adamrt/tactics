#include "psx/types.h"

typedef struct {
    s16 next;
    s16 id;
    u8 unk_04[240];
    s32 unk_F4;
} EffectStateRecord;

extern s16 g_effect_active_index;
extern s16 g_effect_free_index;
extern s16 g_effect_unk_801bf004;
extern s32 g_effect_phase;
extern EffectStateRecord g_effect_state_records[];

void battle_effect_related(void) {
    s32 i;

    g_effect_state_records[0].next = 0;
    g_effect_active_index = 1;
    for (i = 1; i < 16; i++) {
        g_effect_state_records[i].id = i;
        g_effect_state_records[i].next = i + 1;
        g_effect_state_records[i].unk_F4 = 0;
    }
    g_effect_state_records[i].next = 0;
    g_effect_state_records[i].id = i;
    g_effect_free_index = 0;
    g_effect_unk_801bf004 = 0;
    g_effect_phase = 0;
}
