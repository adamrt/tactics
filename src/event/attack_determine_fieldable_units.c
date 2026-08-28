#include "fft/attack.h"
#include "fft/data.h"

#define ATTACK_ROSTER_SLOTS     20
#define ATTACK_GUEST_SLOT_START 16
#define ATTACK_NAME_BYTES       16
#define ATTACK_NAME_END         0xfe
#define PARTY_FLAG_UNDEPLOYABLE 0x04

extern party_data_t* main_get_party_data_pointer(s32 party_index);
extern s32 get_script_variable(s32 variable_id);
extern void set_script_variable(s32 variable_id, s32 value);

extern u8* volatile D_80173fb8;
extern u8* volatile g_battle_text_pointer_2;
extern u8* volatile g_battle_text_pointer_6;
extern u8* volatile g_battle_text_pointer_8;
extern u8* volatile D_80173fe4;
extern s16 D_80173cb0;
extern volatile s32 D_801cd2b4;
extern volatile s32 D_801cd2b8;
extern u8 D_801cd330[];
extern u8 g_attack_unit_fieldable[ATTACK_ROSTER_SLOTS];
extern s32 g_attack_fieldable_unit_count;
extern attack_squad_data_t* g_attack_squad_data;
extern s32 g_attack_current_squad_id;
extern s32 g_battle_entd_selection_mode;

void attack_determine_fieldable_units(void) {
    s32 roster_index;
    s32 name_index;
    s32 name_end;
    s32 final_name_index;
    u8* name_cursor;
    u8* fieldable;
    party_data_t* party_unit;
    u8 name_byte;
    s32 map_id;
    s32 script_variable;
    s32 next_squad;
    s32 first_name_offset;
    s32 second_name_offset;
    /* Pin: the target holds this base in $a0 and `help_text` in $v1; unpinned
     * GCC swaps the two regardless of declaration or assignment order. */
    register u8* unit_names asm("$4");
    u8* help_text;
    attack_squad_data_t* squad;

    roster_index = 0;
    name_end = ATTACK_NAME_END;
    final_name_index = ATTACK_NAME_BYTES - 1;
    name_cursor = D_80173fb8;
    first_name_offset = D_801cd2b4;
    unit_names = D_801cd330;
    help_text = D_80173fe4;
    g_battle_text_pointer_8 = unit_names + first_name_offset;
    second_name_offset = D_801cd2b8;
    g_attack_fieldable_unit_count = 0;
    g_battle_text_pointer_2 = help_text;
    g_battle_text_pointer_6 = unit_names + second_name_offset;
    fieldable = g_attack_unit_fieldable;

    do {
        party_unit = main_get_party_data_pointer(roster_index);
        if (party_unit->party_id == 0xff || roster_index >= ATTACK_GUEST_SLOT_START || party_unit->proposition_status != 0 || (party_unit->gender_flags & PARTY_FLAG_UNDEPLOYABLE) != 0) {
            *fieldable = 0;
            *name_cursor = name_end;
        advance_name_cursor:
            name_cursor++;
            goto next_roster;
        }

        *fieldable = 1;
        g_attack_fieldable_unit_count++;
        name_index = 0;
    copy_name:
        name_byte = party_unit->name[name_index];
        *name_cursor = name_byte;
        if ((name_byte & ATTACK_NAME_END) == name_end) {
            goto advance_name_cursor;
        }
        name_cursor++;
        if (name_index == final_name_index) {
            *name_cursor = name_end;
            name_cursor++;
        }
        name_index++;
        if (name_index < ATTACK_NAME_BYTES) {
            goto copy_name;
        }
    next_roster:
        roster_index++;
        fieldable++;
    } while (roster_index < ATTACK_ROSTER_SLOTS);

    if (D_80173cb0 != 0) {
        return;
    }

    if (g_attack_squad_data[g_attack_current_squad_id].valid_tile_bitmap == 0) {
        g_attack_current_squad_id = 0;
    }

    if (get_script_variable(0x1fe) != 0) {
        map_id = get_script_variable(0x33);
        squad = g_attack_squad_data;
        roster_index = 0;
        g_attack_current_squad_id = 0;
    find_squad:
        if (squad->map_id == map_id) {
            goto found_squad;
        }
        roster_index++;
        squad++;
        if (roster_index < 0x300) {
            goto find_squad;
        }

    squad_selected:
        if (g_attack_squad_data[g_attack_current_squad_id].valid_tile_bitmap == 0) {
            g_attack_current_squad_id = 0;
        }
        set_script_variable(0x34, 2);
        set_script_variable(0x35, g_attack_current_squad_id);
        next_squad = g_attack_current_squad_id;
        if (next_squad != 0) {
            next_squad++;
            goto set_nonzero_next_squad;
        }
        next_squad++;
        script_variable = 0x36;
        next_squad = 0;
        goto set_next_squad;
    found_squad:
        g_attack_current_squad_id = roster_index;
        goto squad_selected;
    set_nonzero_next_squad:
        script_variable = 0x36;
    set_next_squad:
        set_script_variable(script_variable, next_squad);
        set_script_variable(0x39,
            g_attack_squad_data[g_attack_current_squad_id].unit_limit);
        g_attack_squad_data[g_attack_current_squad_id].unit_limit = 4;
    } else {
        g_battle_entd_selection_mode = 0;
        g_attack_current_squad_id = get_script_variable(0x35);
        set_script_variable(0x39,
            g_attack_squad_data[g_attack_current_squad_id].unit_limit);
    }
}
