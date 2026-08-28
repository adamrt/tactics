#include "psx/types.h"

extern s32 CdSync(s32 mode);
extern s32 main_unused_music_stub(void);
extern s32 (*g_call_inner_subroutine_target)();
extern s32 call_inner_subroutine(void);

void attack_wait_for_music_open(void) {
    do {
        CdSync(0);
        g_call_inner_subroutine_target = main_unused_music_stub;
    } while (call_inner_subroutine() != 0);
}
