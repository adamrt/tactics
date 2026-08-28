#include "fft/battle.h"
#include "psx/types.h"

extern s16 g_require_comparison_unit_id;
extern s16 g_require_selected_unit_id;
extern u8 g_require_comparison_billboard[];
extern u8 g_require_selected_billboard[];
extern s16 g_require_unit_type;
extern s16 g_require_brave;
extern s16 g_require_faith;
extern s16 g_require_zodiac;
extern s16 g_require_editor_unit_fields[];
extern u8 g_require_first_ability_bytes[];
extern u8 g_require_second_ability_bytes[];
extern u8 g_require_third_ability_bytes[];
extern u8 g_require_fourth_ability_bytes[];
extern u8 g_item_flags_by_id[];
extern s32 (*g_call_inner_subroutine_target)();

extern battle_stats_t* get_battle_stats_pointer(s32 unit_id);
extern void require_copy_battle_stats_to_status_gauges(battle_stats_t* unit, u8* output);
extern u16* build_filtered_skillset_ability_list(u8 job_id, s32 table);
extern s32 unit_has_adjacent_monster_skill_support(battle_stats_t* unit);
extern u8* main_get_item_data_pointer(s32 item_id);
extern void require_fill_string_buffer_fe(void* destination);
extern void world_copy_bytes(void* destination, const void* source, s32 size);
extern s32 call_inner_subroutine(void* argument);

void require_load_selected_unit_into_editor(void) {
    battle_stats_t* unit;
    s16* editor;
    u16* innate_items;
    s16* ability_slot;
    u8* item;
    s32 i;
    s32 output_index;
    s32 item_id;
    u8 item_flags;
    u8 field_value;
    s16 list_value;

    unit = get_battle_stats_pointer(g_require_comparison_unit_id);
    editor = g_require_editor_unit_fields;
    if (unit != 0) {
        require_copy_battle_stats_to_status_gauges(
            unit, g_require_comparison_billboard);
    }

    unit = get_battle_stats_pointer(g_require_selected_unit_id);
    if (unit == 0)
        return;
    require_copy_battle_stats_to_status_gauges(
        unit, g_require_selected_billboard);

    g_require_unit_type = unit->job_id;
    g_require_brave = unit->brave;
    g_require_faith = unit->faith;
    /* The zodiac sign lives in the top nibble of the halfword at 0x008. */
    g_require_zodiac = *(u16*)&unit->_pad008 >> 12;

    editor[0] = unit->move;
    editor[1] = unit->attributes[2];
    editor[2] = unit->jump;
    editor[5] = unit->evasion[2];
    editor[6] = unit->evasion[3];
    editor[3] = unit->evasion[0];
    editor[4] = unit->evasion[1];
    editor[9] = unit->attributes[0];
    editor[10] = unit->evasion[7];
    editor[11] = unit->evasion[5];
    if (unit->evasion[5] <= unit->evasion[6])
        editor[11] = unit->evasion[6];
    editor[12] = unit->evasion[4];
    editor[14] = unit->attributes[1];
    editor[15] = 0;
    editor[16] = unit->evasion[9];
    if (unit->evasion[9] <= unit->evasion[10])
        editor[16] = unit->evasion[10];
    editor[17] = unit->evasion[8];

    for (i = 4; i >= 0; i--)
        editor[18 + i] = 0;

    if (!(unit->unit_flags & 0x20)) {
        editor[18] = unit->equipment[3] != 0xff ? unit->equipment[3] : unit->equipment[4];
        editor[19] = unit->equipment[5] != 0xff ? unit->equipment[5] : unit->equipment[6];
        editor[20] = unit->equipment[0];
        editor[21] = unit->equipment[1];
        editor[22] = unit->equipment[2];
    }

    for (i = 0; i < 5; i++) {
        if (editor[18 + i] == 0 || editor[18 + i] == 0xff)
            editor[18 + i] = -1;
    }

    editor[7] = 0;
    if ((u8)(unit->primary_skillset + 0x50) < 0x30)
        editor[7] = 1;

    if (editor[7] != 0) {
        innate_items = build_filtered_skillset_ability_list(unit->primary_skillset, 1);
        i = 0;
        ability_slot = editor;
        do {
            ability_slot[23] = *innate_items++;
            i++;
            ability_slot++;
        } while (i < 5);

        g_call_inner_subroutine_target = unit_has_adjacent_monster_skill_support;
        if (call_inner_subroutine(unit) == 0)
            editor[26] = 0;

        output_index = 0;
        for (item_id = 0; item_id < 5; item_id++) {
            if (editor[23 + item_id] != 0)
                editor[23 + output_index++] = editor[23 + item_id];
        }
        while (output_index < 5)
            editor[23 + output_index++] = 0;
    } else {
        field_value = unit->primary_skillset;
        editor[23] = field_value;
        if (field_value == 0)
            g_require_third_ability_bytes[0] = 0xfe;
        field_value = unit->secondary_skillset;
        editor[24] = field_value;
        if (field_value == 0)
            g_require_fourth_ability_bytes[1] = 0xfe;
        editor[25] = unit->reaction_ability;
        editor[26] = unit->support_ability;
        editor[27] = unit->movement_ability;
    }

    for (i = 0; i < 5; i++) {
        list_value = editor[23 + i];
        if (list_value == 0)
            editor[23 + i] = list_value - 1;
    }

    item_id = 0;
    editor[8] = 0;
    if (editor[18] != -1) {
        if (editor[19] == -1)
            item_id = editor[18];
    } else if (editor[19] != -1) {
        item_id = editor[19];
    }

    if (item_id != 0) {
        item = main_get_item_data_pointer(item_id);
        if (item[3] & 0x80) {
            item_flags = g_item_flags_by_id[item_id * 8];
            if ((item_flags & 1) || ((unit->support_abilities[2] & 2) && (item_flags & 4)))
                editor[8] = 1;
        }
    }

    require_fill_string_buffer_fe(g_require_first_ability_bytes);
    require_fill_string_buffer_fe(g_require_second_ability_bytes);
    require_fill_string_buffer_fe(g_require_third_ability_bytes);
    require_fill_string_buffer_fe(g_require_fourth_ability_bytes);
    /* Learned-ability bitmaps for the four displayed skillsets; battle_stats_t
     * keeps the whole 0x099..0x158 region as one learned_abilities[] array. */
    world_copy_bytes(g_require_first_ability_bytes, &unit->learned_abilities[0x12c - 0x99], 0x10);
    world_copy_bytes(g_require_second_ability_bytes, &unit->learned_abilities[0x13c - 0x99], 0x10);
    world_copy_bytes(g_require_third_ability_bytes, &unit->learned_abilities[0x14c - 0x99], 0x10);
    world_copy_bytes(g_require_fourth_ability_bytes, &unit->learned_abilities[0x154 - 0x99], 0x10);
}
