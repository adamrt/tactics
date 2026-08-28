#include "psx/types.h"

extern void memset(void* dst, s32 val, s32 count);
extern u8 g_equip_action_records[];

void equip_clear_all_indexed_action_records(void) {
    memset(g_equip_action_records, 0, 0x1E);
}
