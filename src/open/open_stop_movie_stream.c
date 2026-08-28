#include "psx/types.h"

extern s32 DrawSync(s32 mode);
extern void DecDCToutCallback(void* callback);
extern void StSetDataReadyCallback(void);
extern void open_pause_movie_cd_audio(void);
extern u32 g_open_runtime_flags;

void open_stop_movie_stream(s32 pause_cd_audio) {
    DrawSync(0);
    DecDCToutCallback(0);
    StSetDataReadyCallback();

    if (pause_cd_audio != 0) {
        open_pause_movie_cd_audio();
    }

    g_open_runtime_flags &= ~2;
}
