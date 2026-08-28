#include "psx/types.h"

extern void open_set_sound_type_and_volume(s32 sound_type, s32 duration);
extern s32 CdControlb(s32 command, const u8* parameter, u8* result);
extern s32 VSync(s32 mode);
extern u32 g_open_runtime_flags;

void open_pause_movie_cd_audio(void) {
    if ((g_open_runtime_flags & 4) != 0) {
        open_set_sound_type_and_volume(0, 1);

        while (CdControlb(9, 0, 0) == 0) {
        }

        VSync(4);
        g_open_runtime_flags ^= 4;
    }
}
