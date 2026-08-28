#include "fft/battle.h"
#include "psx/types.h"

extern u8 D_8014D314;
extern battle_stats_t* battle_get_battle_stats_from_battle_id(s32 battle_id);

void battle_store_main_target_id_auto_battle(s8 target_id, s32 battle_id) {
    battle_stats_t* stats = battle_get_battle_stats_from_battle_id(battle_id);
    stats->auto_battle_target = target_id;
    stats->auto_battle_setting = D_8014D314;
}
