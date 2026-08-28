#include "psx/types.h"

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
} BunitOut65E4Entry;

extern BunitOut65E4Entry g_bunit_action_records[];

/* BUNIT.OUT 001c65e4 - Populate the 6-byte record at `index` in the g_bunit_action_records
 * table with a source-id (low 10 bits masked from an indirection table). */
void bunit_set_indexed_action_record(s32 index, s32 field0, s32 field2, u16* lookup_table) {
    g_bunit_action_records[index].f0 = field0;
    g_bunit_action_records[index].f2 = field2;
    g_bunit_action_records[index].f4 = lookup_table[field0] & 0x3FF;
}
