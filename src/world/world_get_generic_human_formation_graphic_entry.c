#include "psx/types.h"

typedef struct {
    u8 data[0xC];
} WorldFormationGraphicEntry;

extern u8 g_world_generic_human_graphic_index_table[];
extern WorldFormationGraphicEntry g_world_formation_graphic_entries[];
extern void bcopy(void* src, void* dst, s32 len);

void world_get_generic_human_formation_graphic_entry(s32 job_id, s16 is_female, void* dst) {
    s16 id = job_id;
    s16 idx;

    if (id < 0x35) {
        idx = g_world_generic_human_graphic_index_table[id];
    } else if (id == 0x5C) {
        idx = 0x3B;
    } else if (id == 0x5B) {
        idx = 0x3A;
    } else {
        if (id == 0x5D) {
            idx = 0x3C;
        } else {
            idx = (job_id * 2) - 0x7C;
        }
        if (is_female != 0) {
            idx += 1;
        }
    }
    bcopy(&g_world_formation_graphic_entries[idx], dst, 0xC);
}
