#include "psx/types.h"

typedef struct {
    u8 high_id_bits[3];
    u8 ability_ids[22];
} HumanSkillsetAbilities;

typedef struct {
    u8 high_id_bits;
    u8 ability_ids[4];
} MonsterSkillsetAbilities;

extern HumanSkillsetAbilities g_human_skillset_abilities[];
extern MonsterSkillsetAbilities g_monster_skillset_abilities[];

s32 main_get_ability_id_from_skillset(s32 skillset_id, s32 ability_index) {
    s32 adjusted_index;
    s32 flag_byte_index;
    /* Pinned: unpinned, $v0/$v1 swap roles in both arms (register-only diff). */
    register s32 high_id_bit __asm__("$2");

    if (skillset_id < 0xb0) {
        u8* table_base;
        u8* ability_entry;

        if (ability_index >= 22) {
            return 0;
        }
        adjusted_index = ability_index;
        table_base = (u8*)g_human_skillset_abilities;
        skillset_id = (s32)(table_base + skillset_id * sizeof(HumanSkillsetAbilities));
        if (ability_index < 0) {
            adjusted_index = ability_index + 7;
        }
        flag_byte_index = adjusted_index >> 3;
        high_id_bit = ((u8*)skillset_id)[flag_byte_index];
        high_id_bit <<= ability_index - flag_byte_index * 8 + 1;
        high_id_bit &= 0x100;
        ability_entry = (u8*)skillset_id + ability_index;
        return ability_entry[3] | high_id_bit;
    }

    if (skillset_id < 0xe0) {
        u8* table_base;
        u8* ability_entry;

        if (ability_index >= 4) {
            return 0;
        }
        adjusted_index = ability_index;
        table_base = (u8*)g_monster_skillset_abilities - 0xb0 * sizeof(MonsterSkillsetAbilities);
        skillset_id = (s32)(table_base + skillset_id * sizeof(MonsterSkillsetAbilities));
        if (ability_index < 0) {
            adjusted_index = ability_index + 7;
        }
        flag_byte_index = adjusted_index >> 3;
        high_id_bit = ((u8*)skillset_id)[flag_byte_index];
        high_id_bit <<= ability_index - flag_byte_index * 8 + 1;
        high_id_bit &= 0x100;
        ability_entry = (u8*)skillset_id + ability_index;
        return ability_entry[1] | high_id_bit;
    }

    return 0;
}
