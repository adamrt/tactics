#include "fft/data.h"
#include "psx/types.h"

#define SKILLSET_ABILITY_COUNT 24

/* 0x80066204: "Temp Ability List (used for setting usable abilities)". */
extern u16 g_temp_ability_list[SKILLSET_ABILITY_COUNT];
extern s32 main_get_ability_id_from_skillset(s32 skillset, s32 index);

/* Copies the skillset's ability ids into g_temp_ability_list, keeping only the
 * classes selected by `flags`: 1 action, 2 reaction, 8 support, 4 movement. */
u16* main_store_skillset_s_abilities(s32 skillset, s32 flags) {
    s32 count;
    s32 i;
    s32 id;
    s32 keep;

    if (skillset >= 0x100) {
        skillset = 0;
    }
    count = 0;
    i = 0;
    do {
        id = main_get_ability_id_from_skillset(skillset, i);
        if ((u32)(id & 0xFFFF) < ABILITY_ID_REACTION_FIRST) {
            keep = flags & 1;
        } else if ((u32)(id & 0xFFFF) < ABILITY_ID_SUPPORT_FIRST) {
            keep = flags & 2;
        } else if ((u32)(id & 0xFFFF) < 0x1E7) {
            /* One past ABILITY_ID_MOVEMENT_FIRST in the original. */
            keep = flags & 8;
        } else {
            keep = flags & 4;
        }
        if (keep == 0) {
            id = 0;
        }
        g_temp_ability_list[count++] = id;
        i += 1;
    } while (i < SKILLSET_ABILITY_COUNT);

    while (count < SKILLSET_ABILITY_COUNT) {
        g_temp_ability_list[count] = 0;
        count += 1;
    }
    return g_temp_ability_list;
}
