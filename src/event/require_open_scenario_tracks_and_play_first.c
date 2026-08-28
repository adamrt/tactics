#include "psx/types.h"

extern void main_unload_scenario_music_and_tunes(void);
extern void open_and_play_music(void);
extern void switch_music_track(void);
extern s32 call_inner_subroutine();
extern void require_wait_for_music_call_idle(void);
extern void (*g_call_inner_subroutine_target)(void);

void require_open_scenario_tracks_and_play_first(s32 first_track,
    s32 second_track) {
    main_unload_scenario_music_and_tunes();
    if (first_track != 0) {
        g_call_inner_subroutine_target = open_and_play_music;
        call_inner_subroutine(first_track, 1);
        require_wait_for_music_call_idle();
    }
    if (second_track != 0) {
        g_call_inner_subroutine_target = open_and_play_music;
        call_inner_subroutine(second_track, 2);
        require_wait_for_music_call_idle();
    }
    if (first_track != 0) {
        g_call_inner_subroutine_target = switch_music_track;
        call_inner_subroutine(1, 0x7f, 0);
    }
}
