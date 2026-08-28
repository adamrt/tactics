#include "psx/etc.h"
#include "psx/types.h"

extern s32 main_unused_music_stub(void);
extern s32 call_inner_subroutine(void);
extern s32 (*g_call_inner_subroutine_target)(void);

void require_wait_for_music_call_idle(void) {
    do {
        VSync(0);
        g_call_inner_subroutine_target = main_unused_music_stub;
    } while (call_inner_subroutine() != 0);
}
