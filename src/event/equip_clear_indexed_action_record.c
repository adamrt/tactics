#include "psx/types.h"

extern void* memset(void* dst, s32 value, s32 count);
extern u8 g_equip_action_records[];

/* EQUIP.OUT 001bfa44 - Clear a 6-byte record at index arg0 in the table at 0x801e12c4. */
void equip_clear_indexed_action_record(s32 index) {
    memset(&g_equip_action_records[index * 6], 0, 6);
}
