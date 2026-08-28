#include "psx/types.h"

typedef struct OpenScriptRecord {
    u32 flags;
    u8 pad_004[0x0c];
    s32 value;
    u8 pad_014[0x150];
} OpenScriptRecord;

extern s32 g_open_script_timing_step;
extern volatile s32 g_open_script_timing_fraction;
extern volatile s32 g_open_script_external_counter;
extern OpenScriptRecord g_open_script_records[16];

void open_update_script_timing_and_record_values(void) {
    s32 step;
    register s32 work __asm__("$5");
    s32 counter;
    s32 index;
    s32 value;
    OpenScriptRecord* record;
    s32* value_pointer;

    step = g_open_script_timing_step;
    if (step == 0) {
        return;
    }

    if (step > 0) {
        counter = g_open_script_timing_fraction;
        work = step + counter;
        step = work & 0xff;
        counter = g_open_script_external_counter;
        work >>= 8;
        g_open_script_timing_fraction = step;
        counter += work;
    } else {
        counter = g_open_script_timing_fraction;
        work = counter - step;
        step = work & 0xff;
        counter = g_open_script_external_counter;
        work >>= 8;
        g_open_script_timing_fraction = step;
        counter += work;
        work = -work;
    }
    g_open_script_external_counter = counter;

    index = 0;
    record = g_open_script_records;
    value_pointer = &record->value;
    do {
        if (record->flags & 1) {
            value = *value_pointer;
            value += work;
            *value_pointer = value;
            if ((u32)(value - 0x10) >= 0xf1) {
                record->flags ^= 1;
            }
        }
        __asm__ volatile("" : : "r"(index));
        record++;
        index++;
        value_pointer = (s32*)((u8*)value_pointer + sizeof(*record));
    } while (index < 16);
}
