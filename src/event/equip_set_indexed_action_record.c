#include "psx/types.h"

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
} EquipFa80Entry;

extern EquipFa80Entry g_equip_action_records[];

void equip_set_indexed_action_record(s32 arg0, s32 arg1, s32 arg2, u16* arg3) {
    g_equip_action_records[arg0].f0 = arg1;
    g_equip_action_records[arg0].f2 = arg2;
    g_equip_action_records[arg0].f4 = arg3[arg1] & 0x3FF;
}
