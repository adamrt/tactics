#include "fft/battle.h"
#include "psx/types.h"

extern s16 g_battle_acting_unit_used_ability_id;
extern s32 main_get_ability_id_from_skillset(s32 skillset, s32 index);

void battle_learn_used_ability(battle_stats_t* unit) {
    u8 learned[3];
    u8 skillset;
    s32 job;
    s32 i;
    s32 byte_idx;
    s32 mask;
    u8* src;
    u8* dst;
    u8* base;
    u8* p;

    job = unit->job_id;
    skillset = unit->primary_skillset;
    if (job < 0x4A) {
        job = 0;
    } else {
        job -= 0x4A;
    }
    /* Three learned-ability bytes per job, from learned_abilities (0x99). */
    dst = learned;
    src = (u8*)(((job * 3) + (s32)unit) + 0x99);
    do {
        *dst = *src;
        dst += 1;
        src += 1;
    } while ((s32)dst < (s32)&learned[3]);
    i = 0;
    base = (u8*)(((job * 3) + (s32)unit) + 0x99);
    do {
        byte_idx = i / 8;
        mask = 0x80 >> (i - (byte_idx * 8));
        if (!(learned[byte_idx] & mask)) {
            if ((u16)main_get_ability_id_from_skillset(skillset, i) == g_battle_acting_unit_used_ability_id) {
                p = base + byte_idx;
                *p = mask | *p;
            }
        }
        i += 1;
    } while (i < 0x18);
}
