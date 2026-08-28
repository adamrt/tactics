#include "fft/battle.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;
extern s32 g_battle_status_menu_enabled;
extern s32 g_battle_casting_unit_id;
extern s32 g_battle_casting_misc_id;
extern void battle_reset_jumping_unit_graphic_triggers(void);
extern void reset_battle_event_state(void);
extern void battle_clear_at_list_active(void);

void battle_set_casting_unit_id_ff(void) {
    g_animation_speed = 2;
    g_battle_game_state = BATTLE_GAME_STATE_EVENT;
    battle_reset_jumping_unit_graphic_triggers();
    reset_battle_event_state();
    battle_clear_at_list_active();
    g_battle_status_menu_enabled = 0;
    g_battle_casting_unit_id = 0xff;
    g_battle_casting_misc_id = 0xff;
}
