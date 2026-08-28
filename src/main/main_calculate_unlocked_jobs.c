#include "fft/job.h"
#include "psx/types.h"

u32 main_calculate_unlocked_jobs(const u8* packed_job_levels, u32 gender_flags) {
    u8 levels[18];
    s32 unlock_bit;
    s32 unlocked;
    s32 job;
    u8* level_out;
    u8* copy_end;
    const u8* requirements_base;

    level_out = levels;
    copy_end = levels + 10;
    do {
        *level_out++ = *packed_job_levels++;
    } while ((s32)level_out < (s32)copy_end);

    if (gender_flags & UNIT_GENDER_FEMALE) {
        levels[8] |= 0x0f;
    }
    if (gender_flags & UNIT_GENDER_MALE) {
        levels[9] |= 0xf0;
    }
    if (gender_flags & UNIT_GENDER_MONSTER) {
        return 0;
    }

    unlock_bit = 0x800000;
    unlocked = 0x800000;
    job = 0;
    requirements_base = &g_job_unlock_requirements[0][0];
    do {
        s32 divided_unlock_bit;

        divided_unlock_bit = unlock_bit + ((u32)unlock_bit >> 31);
        unlock_bit = divided_unlock_bit >> 1;
        {
            register s32 blocked __asm__("$9") = 0;
            const u8* level = levels;
            const u8* requirements = requirements_base;
            const u8* levels_end;

            __asm__ volatile("addiu %0,$29,10" : "=r"(levels_end));

            do {
                u8 requirement = *requirements;
                u8 packed_level;

                __asm__ volatile("" : "=r"(requirement) : "0"(requirement));
                packed_level = *level;

                if (((packed_level & 0xf0) < (requirement & 0xf0)) || ((requirement & 0x0f) > (packed_level & 0x0f))) {
                    blocked = 1;
                    break;
                }
                level++;
                requirements++;
            } while ((s32)level < (s32)levels_end);
            requirements_base += 10;
            if (!blocked) {
                unlocked |= unlock_bit;
            }
        }
        job++;
    } while (job < 19);

    if (gender_flags & UNIT_GENDER_MALE) {
        unlocked &= 0xffffd0;
    }
    if (gender_flags & UNIT_GENDER_FEMALE) {
        unlocked &= 0xffffb0;
    }
    return (u32)unlocked;
}
