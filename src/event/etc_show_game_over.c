#include "psx/types.h"

typedef struct EtcGraphic {
    const char* path;
    s32 lba;
    s32 size;
    void* framebuffer_rect;
    s16* dimensions;
    void* unused_14;
    void* unused_18;
    s32 texture_mode;
} EtcGraphic;

extern EtcGraphic g_etc_graphics[];
extern u8 g_etc_chapter_primitives_a[2][0xd0];
extern s32 g_event_speed;
extern s32 (*g_call_inner_subroutine_target)();

extern s32 call_inner_subroutine();
extern void main_unload_scenario_music_and_tunes(void);
extern s32 main_open_scenario_smd_files(s32 value);
extern s32 main_poll_scenario_smd_file_load(void);
extern s32 switch_music_track(s32 slot, s32 volume, s32 time);
extern void etc_build_game_over_graphic_polygons(
    s32 graphic_id, s32 fade, s32 blend_mode, s32 layer,
    void* primitives, s32 color);
extern void switch_to_next_thread(void);

void etc_show_game_over(s32 graphic_id) {
    /* The target reserves two otherwise unreferenced local words. */
    volatile s32 reserved_stack_words[2];
    s32 frame;
    s32 fade;
    s32 color;
    s16* dimensions;

    g_call_inner_subroutine_target = main_unload_scenario_music_and_tunes;
    call_inner_subroutine();
    g_call_inner_subroutine_target = main_open_scenario_smd_files;
    call_inner_subroutine(0x32);
    do {
        switch_to_next_thread();
        g_call_inner_subroutine_target = main_poll_scenario_smd_file_load;
    } while (call_inner_subroutine() != 0);
    g_call_inner_subroutine_target = switch_music_track;
    call_inner_subroutine(1, 0x7f, 0);

    dimensions = g_etc_graphics[graphic_id].dimensions;
    frame = 0;
    fade = 0;
    if (dimensions[15] > 0) {
        do {
            etc_build_game_over_graphic_polygons(
                graphic_id, fade, 2, 0,
                g_etc_chapter_primitives_a[frame & 1], 0x80);
            frame++;
            switch_to_next_thread();
            fade += g_event_speed;
        } while (fade < dimensions[15]);
    }

    fade = 0;
    do {
        etc_build_game_over_graphic_polygons(
            graphic_id, dimensions[15], 2, 0,
            g_etc_chapter_primitives_a[frame & 1], 0x80);
        frame++;
        switch_to_next_thread();
        fade += g_event_speed;
    } while (fade < 0x258);

    color = 0x80;
    fade = 0;
    do {
        etc_build_game_over_graphic_polygons(
            graphic_id, dimensions[15], 2, 0,
            g_etc_chapter_primitives_a[frame & 1], color);
        color -= g_event_speed;
        switch_to_next_thread();
        fade += g_event_speed;
        frame++;
    } while (fade < 0x80);
}
