#include "psx/types.h"

extern u16 g_jobstts_ability_entries[];
extern s32 g_jobstts_ability_type;
extern u8* g_jobstts_selected_specific_ability;
/* Same target slot; the alias preserves independent a1/a2 materialization. */
extern u8* g_jobstts_selected_specific_ability_arg_alias;
extern s32 main_calculate_ability_pointers_and_type(s32 ability_id, u8** first,
    u8** second);

s32 jobstts_is_non_action_ability_learned(s32 index) {
    u16* entries;
    u16* entry;
    s32 result;
    u16 ability;

    entries = g_jobstts_ability_entries;
    entry = &entries[index];
    g_jobstts_ability_type = main_calculate_ability_pointers_and_type(
        *entry & 0x3ff, &g_jobstts_selected_specific_ability,
        &g_jobstts_selected_specific_ability_arg_alias);
    result = 0;
    if (g_jobstts_ability_type != 0) {
        ability = *entry;
        result = (ability >> 14) == 0;
    }
    return result;
}
