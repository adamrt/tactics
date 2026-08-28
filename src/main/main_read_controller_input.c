#include "psx/types.h"

extern void PAD_dr(void);
extern u32 g_raw_controller_input;

u32 main_read_controller_input(s32 unused) {
    PAD_dr();
    return ~g_raw_controller_input;
}
