#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;

/* Does the unit currently have status bit `status_bit` (0..39), not as an
 * innate status, while the considered ability cancels it? */
s32 battle_check_for_0x00_status(battle_stats_t* unit, s32 status_bit) {
    battle_ai_data_t* ai = &g_ai_data_base;
    u8* stats = (u8*)unit;
    s32 byte_off = status_bit / 8;
    s32 mask = 0x80 >> (status_bit - byte_off * 8);

    if (!(*(stats + byte_off + 0x58) & mask)) {
        return 0;
    }
    if (*(stats + byte_off + 0x4E) & mask) {
        return 0;
    }
    if (!(ai->status_to_cancel[byte_off] & mask)) {
        return 0;
    }
    return 1;
}
