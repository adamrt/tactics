#include "psx/types.h"

extern void world_copy_bytes(void* destination, const void* source, u32 size);
extern const u8 g_world_menu_record_template[8];

void world_initialize_menu_record(u8* record) {
    *(s16*)(record + 0x1c) = 0;
    *(s16*)(record + 0x26) = 0;
    world_copy_bytes(record + 0x20, g_world_menu_record_template, 8);
}
