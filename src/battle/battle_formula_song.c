#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_force_sleeping_target_miss(void);
extern int calculate_dance_song_hit(void);
extern void battle_store_ma_and_y(void);
extern void apply_song_ability(void);

void battle_formula_song(void) {
    battle_force_sleeping_target_miss();
    if (g_target_current_action->hit != 0) {
        if (calculate_dance_song_hit() == 0) {
            battle_store_ma_and_y();
            apply_song_ability();
        }
    }
}
