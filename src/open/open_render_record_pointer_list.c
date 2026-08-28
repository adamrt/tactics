#include "psx/types.h"

typedef struct OpenRenderRecord {
    u32 flags;
} OpenRenderRecord;

extern u32 g_open_runtime_flags;

extern void func_80068D80(OpenRenderRecord* record, u32* otag);
extern void func_8006920C(OpenRenderRecord* record, u32* otag);

void open_render_record_pointer_list(
    u32* otag,
    OpenRenderRecord** records,
    s32 count) {
    s32 i;
    register OpenRenderRecord** current __asm__("$17");
    OpenRenderRecord* record;
    u32 flags;
    s32 stack_padding[2];

    if ((g_open_runtime_flags & 8) != 0 || count <= 0) {
        return;
    }

    i = 0;
    current = records;
    do {
        record = *current;
        flags = record->flags;
        if ((flags & 0x18) == 0) {
            if ((flags & 1) != 0) {
                func_80068D80(record, otag);
            } else if ((flags & 2) != 0) {
                func_8006920C(record, otag);
            }
        }
        i++;
        current++;
    } while (i < count);

    /* Preserve the retail function's otherwise unused 0x30-byte stack frame. */
}
