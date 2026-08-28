#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern u8 g_ai_unit_crystal_treasure_status;
extern u8 D_8019F3DC;
extern s32 func_8019D294(void* coords);

void battle_check_unit_for_crystal_or_treasure_status(void) {
    s32 unit_id;
    battle_stats_t* unit;

    g_ai_unit_crystal_treasure_status = 0;
    unit_id = func_8019D294(&D_8019F3DC);
    if (unit_id != 0x15) {
        unit = &battle_stats[unit_id];
        if (unit->entd_slot != 0xFF) {
            if (unit->current_status[0] & 0x40) {
                g_ai_unit_crystal_treasure_status = 1;
            }
            if (unit->current_status[1] & 1) {
                g_ai_unit_crystal_treasure_status = 2;
            }
        }
    }
}
