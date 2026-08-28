#include "psx/etc.h"
#include "psx/gpu.h"
#include "psx/spu.h"
#include "psx/types.h"

extern u32 g_startup2_has_run;
extern u32 g_play_time_frames;
extern u32 g_play_time_seconds;
extern u32 g_play_time_minutes;
extern u32 g_play_time_hours;

extern void main_clear_game_allocator_table(void);
extern void main_unload_scenario_music_and_tunes(void);
extern void main_reset_cdrom_cpu_ram(void);
extern void main_reset_display(int, int, int, u8, u8, u8);
extern void main_build_draw_squaresoft_logo(void);
extern void main_scus_opengnrcsfx(void);
extern void main_get_zodiac_frame(void);
extern void main_initialize_save_state_and_options(void);
extern void main_initialize_status_check_data(void);
extern void initialize_save_data_tables(void);
extern void main_initialize_item_order_tables(void);
extern void main_squaresoft_fade_out(void);

void main_startup2(void) {
    int frame;

    if (g_startup2_has_run != 0) {
        main_clear_game_allocator_table();
        main_unload_scenario_music_and_tunes();
        g_play_time_hours = 0;
        g_play_time_minutes = 0;
        g_play_time_seconds = 0;
        g_play_time_frames = 0;
        ResetGraph(1);
        SetGraphDebug(0);
        SsUtReverbOn();
        main_reset_cdrom_cpu_ram();
        main_reset_display(256, 240, 512, 0, 0, 0);
        main_build_draw_squaresoft_logo();
        main_scus_opengnrcsfx();
        main_get_zodiac_frame();
    }

    main_initialize_save_state_and_options();
    main_initialize_status_check_data();
    initialize_save_data_tables();
    main_initialize_item_order_tables();

    if (g_startup2_has_run != 0) {
        for (frame = 0; frame < 60; frame++) {
            VSync(0);
        }
        main_squaresoft_fade_out();
    }

    g_startup2_has_run = 1;
}
