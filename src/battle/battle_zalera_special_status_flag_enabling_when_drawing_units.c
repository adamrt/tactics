#include "psx/types.h"

extern u8* battle_get_battle_stats_from_battle_id(s32);
extern void func_80068E80(void);
extern void call_inner_subroutine(s32, s32, s32);
extern void (*g_call_inner_subroutine_target)(void);

void battle_zalera_special_status_flag_enabling_when_drawing_units(s32 battle_id, s32 arg1) {
    u8* stats;
    s32 i;
    s32 mask;

    stats = battle_get_battle_stats_from_battle_id(battle_id);
    g_call_inner_subroutine_target = func_80068E80;
    for (i = 0; i < 0x28; i++) {
        mask = 0x80 >> (i % 8);
        if (((stats + i / 8)[0x58] & mask) != 0) {
            call_inner_subroutine(i + 1, arg1, battle_id);
        }
    }
}
