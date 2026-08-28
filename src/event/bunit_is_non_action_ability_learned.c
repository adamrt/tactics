#include "psx/types.h"

extern u16 g_bunit_ability_entries[];
extern s32 g_bunit_ability_type;
extern u8* g_bunit_selected_ability_data_1;
extern u8* g_bunit_selected_specific_ability;

extern s32 main_calculate_ability_pointers_and_type(
    s32 ability_id, u8** ability_data_1, u8** specific_ability_data);

s32 bunit_is_non_action_ability_learned(s32 index) {
    u16* entries;
    u16* entry;
    s32 result;
    u16 ability;

    entries = g_bunit_ability_entries;
    entry = &entries[index];
    g_bunit_ability_type = main_calculate_ability_pointers_and_type(
        *entry & 0x3ff, &g_bunit_selected_ability_data_1,
        &g_bunit_selected_specific_ability);
    result = 0;
    if (g_bunit_ability_type != 0) {
        ability = *entry;
        result = (ability >> 14) == 0;
    }
    return result;
}
