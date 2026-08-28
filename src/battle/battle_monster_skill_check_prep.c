#include "fft/battle.h"
#include "psx/types.h"

extern void func_8017C158(u8*, s32);
extern s32 func_80182508(s32, s32, s32, s32);

s32 battle_monster_skill_check_prep(battle_stats_t* unit) {
    u8 buf[8];
    s32 team;
    s32 x;
    s32 y;
    s32 w;
    s32 sum;

    if (unit->entd_slot == 0xFF) {
        return 0;
    }
    func_8017C158(buf, unit->misc_unit_id);
    team = unit->team_flags;
    x = unit->x;
    y = unit->position.bits.y;
    w = buf[6];
    sum = func_80182508(team, x - 1, y, w) + func_80182508(team, x + 1, y, w);
    sum += func_80182508(team, x, y - 1, w);
    return sum + func_80182508(team, x, y + 1, w);
}
