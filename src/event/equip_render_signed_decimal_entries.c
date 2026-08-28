#include "psx/types.h"

typedef struct EquipStatEntry {
    u16 unk0;
    u16 unk2;
    s16* value;
    u16 flags;
    u16 unkA;
} EquipStatEntry;

typedef struct EquipStatOut {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    s32 unk8;
    u32 unkC;
} EquipStatOut;

extern void func_801C2EC0(s32 value, s32 flags, void* arg2, EquipStatOut* out);

void equip_render_signed_decimal_entries(void* arg0, EquipStatEntry* entry,
    EquipStatOut* out, s32 count) {
    s32 i;
    s32 val;

    for (i = 0; i < count; i++) {
        val = *entry->value;
        out->unk0 = entry->unk0;
        out->unk2 = entry->unk2;
        entry->flags &= 0xf3ff;
        if (val < 0) {
            out->unkC = 0x88888888;
            val = -val;
            entry->flags |= 0x800;
        } else if (val > 0) {
            out->unkC = 0xcccccccc;
            entry->flags |= 0x400;
        } else {
            out->unkC = 0;
            entry->flags |= 0x800;
        }
        func_801C2EC0(val, (s16)entry->flags, arg0, out);
        out->unkC = 0;
        entry++;
    }
}
