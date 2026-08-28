#include "psx/types.h"

extern s32 battle_get_battle_unit_index_by_entd_unit_id(s32);
extern u8* battle_get_battle_stats_from_battle_id(s32);
extern void func_8014CEB4(s32, s32);
extern void resolve_unit_status_changes(void);
extern void (*g_call_inner_subroutine_target)(void);

void battle_inflict_unit_status_by_entd_unit_id(s32 entd_id, s32 status, s32 which,
    s32 arg) {
    s32 idx;
    u8* p;
    s32 i;
    s32 byte;
    s32 bit;

    idx = battle_get_battle_unit_index_by_entd_unit_id(entd_id);
    if (idx == 0x7D0) {
        return;
    }
    p = battle_get_battle_stats_from_battle_id(idx);
    for (i = 0; i < 5; i++) {
        *(p + i + 0x1A7) = 0;
        *(p + i + 0x1AC) = 0;
    }
    byte = status / 8;
    bit = 1 << (status % 8);
    if (which != 0) {
        *(p + byte + 0x1A7) = bit;
    } else {
        *(p + byte + 0x1AC) = bit;
    }
    g_call_inner_subroutine_target = resolve_unit_status_changes;
    func_8014CEB4(idx, arg);
}
