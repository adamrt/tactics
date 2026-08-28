#include "psx/types.h"

typedef struct DiscReadState {
    s32 unknown_0;
    s32 busy;
} DiscReadState;

extern void CdFlush(void);
extern s32 CdControlb(s32 command, const u8* parameter, u8* result);
extern s32 VSync(s32 mode);

void main_reset_pause_cdrom(DiscReadState* state) {
    state->busy = 0;
    CdFlush();
    while (CdControlb(9, 0, 0) == 0) {
    }
    VSync(3);
}
