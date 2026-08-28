#include "psx/types.h"

extern void main_unload_scenario_music_and_tunes(void);
extern s32 open_and_play_music(s32 track, s32 slot);
extern s32 switch_music_track(s32 slot, s32 volume, s32 time);
extern s32 (*g_call_inner_subroutine_target)();
extern s32 call_inner_subroutine();
extern void attack_wait_for_music_open(void);

void attack_play_scenario_music(s32 primary_track, s32 alternate_track) {
    main_unload_scenario_music_and_tunes();

    if (primary_track != 0) {
        g_call_inner_subroutine_target = open_and_play_music;
        call_inner_subroutine(primary_track, 1);
        attack_wait_for_music_open();
    }

    if (alternate_track != 0) {
        g_call_inner_subroutine_target = open_and_play_music;
        call_inner_subroutine(alternate_track, 2);
        attack_wait_for_music_open();
    }

    if (primary_track != 0) {
        g_call_inner_subroutine_target = switch_music_track;
        call_inner_subroutine(1, 0x7f, 0);
    }
}
