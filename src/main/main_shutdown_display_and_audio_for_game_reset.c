#include "psx/gpu.h"

extern void set_all_voices_release_shift_to_6(void);
extern void SpuQuit(void);

void main_shutdown_display_and_audio_for_game_reset(void) {
    DrawSync(0);
    DrawSync(0);
    SetDispMask(0);
    set_all_voices_release_shift_to_6();
    SpuQuit();
}
