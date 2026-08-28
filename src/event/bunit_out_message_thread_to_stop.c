#include "psx/types.h"

extern void func_8014CA38(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void bunit_out_message_thread_to_stop(s32 arg0) {
    func_8014CA38(arg0, 0, 0, 1);
}
