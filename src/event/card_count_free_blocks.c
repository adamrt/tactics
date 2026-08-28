#include "psx/types.h"

typedef struct CardDirectoryEntry {
    u8 name[20];
    u32 attributes;
    s32 size;
    u8 remainder[12];
} CardDirectoryEntry;

s32 card_count_free_blocks(const CardDirectoryEntry* entries, s32 entry_count) {
    s32 i;
    s32 used_blocks;

    used_blocks = 0;
    for (i = 0; i < entry_count; i++) {
        used_blocks += entries[i].size >> 13;
        used_blocks += !!(entries[i].size % 0x2000);
    }

    if (used_blocks >= 16) {
        return 0;
    }
    return 15 - used_blocks;
}
