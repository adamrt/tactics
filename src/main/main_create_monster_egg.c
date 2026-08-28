#include "fft/data.h"

extern s32 main_generate_party_unit(s32 unit_type);
extern party_data_t* main_get_party_data_pointer(s32 party_index);
extern s32 main_calculate_zodiac_symbol(s32 birthday);

s32 main_create_monster_egg(s32 monster_job, s32 egg_modifier, s32 egg_color) {
    s32 party_index;
    /* Pinned: unpinned, party_data and egg_modifier swap $s0/$s1 (a u16 or
     * s32 modifier copy also reorders the other saved registers). */
    register party_data_t* party_data __asm__("$17");
    s32 zodiac;
    u32 zodiac_value;
    u32 egg_modifier_high_bit;

    party_index = main_generate_party_unit(3);
    if (party_index == -1) {
        return party_index;
    }
    party_data = main_get_party_data_pointer(party_index);
    party_data->job_id = monster_job;
    ((u8*)party_data)[0xd2] = egg_color;
    party_data->gender_flags |= 4;
    if ((u16)egg_modifier >= 0x16e) {
        egg_modifier = 1;
    }
    zodiac = main_calculate_zodiac_symbol((u16)egg_modifier);
    party_data->birthday_day = egg_modifier;
    zodiac_value = (unsigned int)zodiac << 4;
    egg_modifier_high_bit = ((unsigned int)egg_modifier & 0x100) >> 8;
    party_data->zodiac = egg_modifier_high_bit + zodiac_value;
    return party_index;
}
