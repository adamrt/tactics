#ifndef FFT_JOB_H
#define FFT_JOB_H

#include "psx/types.h"

enum {
    JOB_ID_SPECIAL_MONSTER_1_FIRST = 0x3c,
    JOB_ID_SPECIAL_MONSTER_1_COUNT = 0x0e,
    JOB_ID_SQUIRE = 0x4a,
    JOB_ID_MIME = 0x5d, /* last generic job (wiki page 00000049) */
    JOB_ID_SPECIAL_MONSTER_2_FIRST = 0x90,
    JOB_ID_SPECIAL_MONSTER_2_COUNT = 0x0b,
    JOB_ID_COUNT = 0xa0,
};

enum UnitGenderFlags {
    UNIT_GENDER_EGG = 0x04, /* "Is an Egg" (wiki page 00000309, 0x04 / 0x70) */
    UNIT_GENDER_MONSTER = 0x20,
    UNIT_GENDER_FEMALE = 0x40,
    UNIT_GENDER_MALE = 0x80,
};

/* world_formation_unit_t.support_sets_3 bits (fft/data.h), fixed by their readers
 * world_check_two_swords / world_check_two_hands / world_check_secret_hunt. */
enum {
    WORLD_SUPPORT_SET_3_TWO_SWORDS = 0x01,
    WORLD_SUPPORT_SET_3_TWO_HANDS = 0x02,
    WORLD_SUPPORT_SET_3_SECRET_HUNT = 0x40,
};

extern const u8 g_job_unlock_requirements[19][10];
extern const u16 g_job_level_jp_requirements[8];

u32 calculate_unlocked_jobs(const u8 job_levels[10], u32 gender_flags);

#endif
