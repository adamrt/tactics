#include "psx/types.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    s16 unk4;
} EquipActionRecord;

extern EquipActionRecord g_equip_action_records[];

void equip_restore_list_selection_from_action_record(s32 idx, s16* p1, s16* p2, s16* list) {
    s32 i;
    s32 found;
    s32 key;

    found = 0;
    *p1 = g_equip_action_records[idx].unk0;
    *p2 = g_equip_action_records[idx].unk2;
    key = g_equip_action_records[idx].unk4;

    for (i = 0; i < *p1; i++) {
        if (list[i] == -1) {
            found = 1;
        }
    }

    if (key == list[*p1] && !found) {
        return;
    }

    for (i = 0; list[i] != -1; i++) {
        if ((((u16*)list)[i] & 0x3FF) == key) {
            *p1 = i;
            return;
        }
    }

    *p1 = 0;
    *p2 = 0;
}
