#include "psx/types.h"

extern u32 g_frontend_world_result;
extern u8 g_go_straight_to_battle;
extern u32 g_game_flow_state;

extern void main_new_game_set_inventory(void);
extern void main_startup2(void);
extern int main_open_exec_open_bin_1(int mode);
extern int main_open_world_and_wldcore(int mode);
extern void main_open_exec_battle_bin(void);
extern void battle_game_loop(void);
extern void main_stop_weather_sfx_music(void);
extern void main_shutdown_display_and_audio_for_game_reset(void);
extern void main_unload_scenario_music_and_tunes(void);
extern void set_script_variable(int variable, int value);
extern void main_open_exec_open_bin_2(void);
extern void main_get_zodiac_frame(void);

void main_game_loop(void) {
    int skip_startup2_state = 5;
    int reset_game_state = 2;
    int credits_game_state = 3;
    int open_mode;
    int open_result;

    g_frontend_world_result = 0;

initialize_frontend:
    main_new_game_set_inventory();

    if (g_frontend_world_result == skip_startup2_state) {
        open_mode = 1;
    } else {
        main_startup2();
        open_mode = 0;
    }

    open_result = main_open_exec_open_bin_1(open_mode);
    if (open_result == 0) {
        g_go_straight_to_battle = 1;
        g_frontend_world_result = 0;
        goto open_world;
    }
    goto open_result_nonzero;

shutdown_and_check:
    main_shutdown_display_and_audio_for_game_reset();
    goto check_credits;

open_result_nonzero:
    g_go_straight_to_battle = 0;

open_world:
    if (g_go_straight_to_battle == 0) {
        g_frontend_world_result = main_open_world_and_wldcore(1);
    }

    if (g_frontend_world_result != skip_startup2_state) {
        main_open_exec_battle_bin();
        battle_game_loop();
        main_stop_weather_sfx_music();
        g_go_straight_to_battle = 0;

        if (g_game_flow_state == reset_game_state) {
            goto shutdown_and_check;
        }

        if (g_game_flow_state != credits_game_state) {
            goto open_world;
        }
    }

check_credits:
    if (g_game_flow_state != credits_game_state) {
        goto initialize_frontend;
    }

    main_stop_weather_sfx_music();
    main_unload_scenario_music_and_tunes();
    set_script_variable(0x64, 1);
    set_script_variable(0x27, 0x12a);
    main_open_exec_open_bin_2();
    main_open_exec_battle_bin();
    main_get_zodiac_frame();
    battle_game_loop();
    main_shutdown_display_and_audio_for_game_reset();
    goto initialize_frontend;
}
