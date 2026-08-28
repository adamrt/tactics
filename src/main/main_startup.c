#include "psx/cd.h"
#include "psx/etc.h"
#include "psx/gpu.h"
#include "psx/libc.h"
#include "psx/spu.h"
#include "psx/types.h"

extern u32 g_play_time_frames;
extern u32 g_play_time_seconds;
extern u32 g_play_time_minutes;
extern u32 g_play_time_hours;
extern u32 g_startup2_has_run;

extern void main_clear_game_allocator_table(void);
extern void main_vsync_callback_func(void);
extern void main_draw_sync_callback_func(void);
extern void main_cd_ready_callback_func(void);
extern void main_cd_read_callback_func(void);
extern void main_reset_cdrom_cpu_ram(void);
extern void main_reset_display(int, int, int, u8, u8, u8);
extern void main_build_draw_sceap(void);
extern void main_build_draw_squaresoft_logo(void);
extern void init_memcard_events(void);
extern void main_scus_opengnrcsfx(void);
extern void main_get_zodiac_frame(void);
extern void main_squaresoft_fade_out(void);

void main_startup(void) {
    main_clear_game_allocator_table();
    ResetCallback();

    g_play_time_hours = 0;
    g_play_time_minutes = 0;
    g_play_time_seconds = 0;
    g_play_time_frames = 0;

    VSyncCallback(main_vsync_callback_func);
    DrawSyncCallback(main_draw_sync_callback_func);
    CdReadyCallback(main_cd_ready_callback_func);
    CdReadCallback(main_cd_read_callback_func);

    ResetGraph(0);
    SetGraphDebug(0);
    PadInit(0);
    SsUtReverbOff();
    main_reset_cdrom_cpu_ram();
    main_reset_display(256, 240, 512, 0, 0, 0);
    main_build_draw_sceap();
    main_build_draw_squaresoft_logo();
    init_memcard_events();
    main_scus_opengnrcsfx();
    main_get_zodiac_frame();
    srand(1);
    main_squaresoft_fade_out();
    g_startup2_has_run = 0;
}
