#include "fft/battle.h"
#include "psx/types.h"

extern u8* main_get_party_data_pointer(s32 index);
extern battle_stats_t* get_battle_stats_pointer(s32 index);
extern battle_stats_t* find_unit_by_id(u32 unit_id, s32* battle_index);
extern void store_equipment_or_sell_overflow(s32 battle_index);
extern void sell_equipment_over_inventory_limit(s32 battle_index);
extern void main_remove_unit_from_party(u32 party_id);
extern void save_unit_to_party(battle_stats_t* unit, s32 is_guest);
extern void require_update_bio_variable_for_unit_class(s32 sprite_id,
    s32 variable);
extern s32 get_script_variable(s32 index);

extern u8 g_require_formation_sprite_groups[];
extern s32 g_require_affected_unit_count;
extern s32 g_require_affected_unit_message_args[];
extern s32 g_require_affected_unit_message_ids[];
extern s32 g_require_affected_battle_unit_indices[];

s32 require_collect_post_battle_join_candidates(void) {
    s32 prompt_count = 0;
    s32 party_index = 0;
    s32 absent = 0xff;
    s32 found_index;

    g_require_affected_unit_count = 0;
    do {
        u8* party_unit = main_get_party_data_pointer(party_index);
        s32 battle_index = 0;

        if (party_unit[1] != absent) {
            register battle_stats_t* unit __asm__("$16");
            do {
                unit = get_battle_stats_pointer(battle_index);
                if (unit->formation_index == party_index && unit->existence != absent && unit->unit_id != 0)
                    break;
                battle_index++;
            } while (battle_index < 0x15);

            if (battle_index != 0x15) {
                unit = get_battle_stats_pointer(battle_index);
                unit = find_unit_by_id(unit->unit_id, &found_index);
                __asm__("" : "=r"(unit) : "0"(unit));
                if (unit->existence == 0x80 || unit->existence == absent || found_index == -3) {
                    if (unit->unit_id == 0 || unit->unit_id >= 4) {
                        if (!(unit->current_status[1] & 1))
                            store_equipment_or_sell_overflow(battle_index);
                        main_remove_unit_from_party(party_index);
                        require_update_bio_variable_for_unit_class(unit->character_identity,
                            0xf);
                    }
                } else if (unit->character_identity != 0 && unit->character_identity < 4) {
                    save_unit_to_party(unit, 0);
                } else if (!(unit->unit_flags & 1) && unit->formation_index >= 0x10) {
                    main_remove_unit_from_party(unit->formation_index);
                    unit->formation_index = absent;
                } else {
                    save_unit_to_party(unit, unit->unit_flags & 1);
                }
            }
        }
        party_index++;
    } while (party_index < 0x14);

    party_index = 0;
    absent = (s32)g_require_formation_sprite_groups;
    do {
        battle_stats_t* unit;
        battle_stats_t* battle_unit;

        battle_unit = get_battle_stats_pointer(party_index);
        unit = find_unit_by_id(battle_unit->unit_id, &found_index);
        if (found_index >= 0 && party_index == found_index && unit->formation_index == 0xff && unit->unit_id != 0) {
            u32 base_class = unit->character_identity;
            if ((base_class == 0 || base_class >= 4) && unit->unit_id >= 4 && ((unit->unit_flags & 0x10) || (unit->current_status[1] & 0x40))) {
                if (unit->unit_flags & 1) {
                    register s32 row __asm__("$17") = 0;
                    s32 sprite = base_class;
                    u8* group = (u8*)absent;

                    for (;;) {
                        s32 column = 0;
                        u8* entry = group;
                        for (; column < 3; column++) {
                            if (sprite == *entry)
                                break;
                            entry++;
                        }
                        {
                            register s32 three __asm__("$2") = 3;
                            if (column != three)
                                goto reset_formation_row;
                        }
                        {
                            s32 rows = 0x49;
                            __asm__ __volatile__("" : "=r"(rows) : "0"(rows));
                        }
                        row++;
                        if (row >= 0x49)
                            break;
                        group += 3;
                    }
                    {
                        s32 rows = 0x49;
                        __asm__ __volatile__("" : "=r"(rows) : "0"(rows));
                    }
                reset_formation_row:
                    row = 0;
                    __asm__ __volatile__("" : "=r"(row) : "0"(row));

                    sell_equipment_over_inventory_limit(party_index);
                    save_unit_to_party(unit, unit->unit_flags & 1);
                } else {
                    s32 count;
                    s32 offset;
                    s32 script_index = 0x21;
                    s32 script_variant;
                    unit->unit_flags &= 0xf6;
                    g_require_affected_unit_message_args[g_require_affected_unit_count] = unit->unit_id;
                    script_variant = get_script_variable(script_index) & 7;
                    prompt_count++;
                    count = g_require_affected_unit_count;
                    offset = count << 2;
                    *(s32*)((u8*)g_require_affected_unit_message_ids + offset) = ((unit->character_identity - 0x80) << 3) + script_variant + 0x1800;
                    *(s32*)((u8*)g_require_affected_battle_unit_indices + offset) = party_index;
                    g_require_affected_unit_count = count + 1;
                }
            }
        }
        party_index++;
    } while (party_index < 0x15);
    return prompt_count;
}
