#include "fft/data.h"
#include "fft/job.h"

extern s32 world_special_monster_check(s32 job_id);

s32 world_lock_equipment_and_abilities(s32 unit_id) {
    world_formation_unit_t* unit;

    unit = g_world_formation_unit_pointers[unit_id];
    if (unit->proposition_status != 0)
        return -2;
    if (unit->unk_3e != 0)
        return -3;
    if (world_special_monster_check(unit->job_id) != 0)
        return -3;
    {
        world_formation_unit_t* u2 = g_world_formation_unit_pointers[unit_id];
        if (u2->gender_flags & UNIT_GENDER_EGG)
            return -4;
        if (u2->job_id == JOB_ID_MIME)
            return -6;
    }
    return 1;
}
