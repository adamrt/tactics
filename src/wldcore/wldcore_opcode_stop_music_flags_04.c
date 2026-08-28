#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u16 D_800D4872;
extern void main_stop_weather_sfx_music(void);

void wldcore_opcode_stop_music_flags_04(void) {
    u16 flags;

    main_stop_weather_sfx_music();
    flags = g_wldcore_state_flags;
    D_800D4872 = 0;
    g_wldcore_state_flags = flags | 4;
}
