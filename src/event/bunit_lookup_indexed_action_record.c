#include "psx/types.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
} BunitActionRecord;

extern BunitActionRecord g_bunit_action_records[];

void bunit_lookup_indexed_action_record(s32 index, s16* out_index, s16* out_b, s16* list) {
    s32 target;
    s32 i;

    *out_index = g_bunit_action_records[index].unk00;
    *out_b = g_bunit_action_records[index].unk02;
    target = g_bunit_action_records[index].unk04;
    if (target == list[*out_index]) {
        return;
    }
    i = 0;
    if (list[0] != -1) {
        do {
            if ((*list & 0x3FF) == target) {
                *out_index = i;
                return;
            }
            list++;
            i++;
        } while (*list != -1);
    }
    *out_index = 0;
    *out_b = 0;
}
