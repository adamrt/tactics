#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* get_battle_stats_pointer(s32 id);
extern void func_801C6920(battle_stats_t* stats, u8* dst);

extern u8 D_801E8DB4[];
extern s16 D_801E8DAC;
extern s16 D_801E8DB0;
extern s16 D_801E8DBA;
extern s16 D_801E8DD2;
extern u8* g_equip_unit_data;
extern u8* D_801E92E8;

void equip_load_unit_data_from_battle_stats(s32 battle_id) {
    battle_stats_t* stats;
    s32 i;
    s32 count;
    u16 tmp0;
    u16 tmp1;

    stats = get_battle_stats_pointer(battle_id);
    func_801C6920(stats, D_801E8DB4);
    count = 0;
    tmp0 = stats->hp;
    tmp1 = stats->mp;
    D_801E8DAC = tmp0;
    D_801E8DB0 = tmp1;

    for (i = 0; i < 0x15; i++) {
        stats = get_battle_stats_pointer(i);
        if (stats == 0) {
            continue;
        }
        if (stats->entd_slot == 0xff) {
            continue;
        }
        if (stats->unit_flags & 4) {
            count++;
            continue;
        }
        if (stats->current_status[0] & 0x40) {
            continue;
        }
        if (stats->current_status[1] & 1) {
            continue;
        }
        count++;
    }

    {
        s16* p = &D_801E8DBA;

        *p = count;
        D_801E8DD2 = battle_id;
        g_equip_unit_data = (u8*)p - 6;
        D_801E92E8 = (u8*)p + 0x74;
    }
}
