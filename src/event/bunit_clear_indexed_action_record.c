#include "psx/types.h"

extern void* memset(void* dst, s32 value, s32 count);
extern u8 g_bunit_action_records[];

/* BUNIT.OUT 001c65a8 - Clear a 6-byte record at index arg0 in the table at 0x801eb22c. */
void bunit_clear_indexed_action_record(s32 index) {
    memset(&g_bunit_action_records[index * 6], 0, 6);
}
