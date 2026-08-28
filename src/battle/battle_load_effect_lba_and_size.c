#include "psx/types.h"

typedef struct EffectDiscEntry {
    s32 lba;
    s32 byte_length;
} EffectDiscEntry;

extern EffectDiscEntry g_effect_disc_entries[];

void battle_load_effect_lba_and_size(s32 effect_id, s32* lba, s32* byte_length) {
    volatile u32 stack_padding[2];

    *lba = g_effect_disc_entries[effect_id].lba;
    *byte_length = g_effect_disc_entries[effect_id].byte_length;
}
