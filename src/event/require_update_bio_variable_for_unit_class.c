#include "psx/types.h"

typedef struct RequireBioUpdateRecord {
    u16 unit_ids[3];
} RequireBioUpdateRecord;

extern RequireBioUpdateRecord g_require_bio_update_records[11];
extern void set_script_variable(u16 variable, s32 value);

void require_update_bio_variable_for_unit_class(s32 unit_class, s32 value) {
    register s32 record_index __asm__("$16") = 0;
    s32 unit_index;
    u16* record = (u16*)g_require_bio_update_records;
    u16* unit;
    s32 offset;
    register s32 unit_limit __asm__("$2");

    do {
        unit_index = 0;
        offset = record_index * 8;
        unit = record;
    scan_units:
        if (unit_class != *unit) {
            unit_index++;
            unit++;
            if (unit_index >= 3) {
            } else {
                goto scan_units;
            }
        }
        unit_limit = 3;
        record += 4;
        if (unit_index != unit_limit) {
            set_script_variable(*(const u16*)((const u8*)g_require_bio_update_records + offset + 6),
                value);
        }
        record_index++;
    } while (record_index < 11);
}
