#include "psx/types.h"

typedef struct OptionMenuRecord {
    u8 unknown_00[0x1c];
    s16 cursor;
    u8 unknown_1e[8];
    s16 scroll_offset;
} OptionMenuRecord;

extern const u8 g_option_menu_record_template[8];
extern void world_copy_bytes(void* destination, const void* source, s32 size);

/* Reset the mutable fields and restore the embedded menu template. */
void option_initialize_menu_record(OptionMenuRecord* record) {
    record->cursor = 0;
    record->scroll_offset = 0;
    world_copy_bytes((u8*)record + 0x20, g_option_menu_record_template, 8);
}
