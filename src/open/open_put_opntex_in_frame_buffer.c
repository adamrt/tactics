#include "psx/gpu.h"
#include "psx/types.h"

void open_put_opntex_in_frame_buffer(const void* source_data) {
    const u8* source;
    const u32* record;
    RECT destination;
    s32 record_word_offset;
    s32 width;
    u32 record_offset;
    u16 width_multiplier;
    register s32 scaled_width __asm__("$7");
    register u32* image_data __asm__("$5");
    s32 record_byte_offset;
    register RECT* destination_ptr __asm__("$4");
    s32 one;
    s32 stack_padding[4];

    source = source_data;
    image_data = (u32*)(source + 20);
    if (*(const u32*)(source + 4) & 8) {
        record_offset = *(const u32*)(source + 8);
        destination.x = *(const volatile s32*)(source + 12);
        destination.y = *(const u16*)(source + 14);
        width = *(const volatile s32*)(source + 16);
        destination.w = width;
        width_multiplier = *(const u16*)(source + 18);
        __asm__ volatile("mult %0,%1"
            :
            : "r"(width), "r"(width_multiplier));
        destination_ptr = &destination;
        record_word_offset = (record_offset >> 2) + 2;
        one = 1;
        destination.h = width_multiplier;
        __asm__ volatile("" : : "m"(destination.w), "m"(destination.h));
        destination.h = one;
        __asm__ volatile("mflo %0" : "=r"(scaled_width));
        destination.w = scaled_width;
        LoadImage(destination_ptr, image_data);
    } else {
        record_word_offset = 2;
    }

    record_byte_offset = record_word_offset * 4;
    __asm__("addu %0,%1,%2"
        : "=r"(record)
        : "r"(record_byte_offset), "r"(source));
    destination.x = *(const volatile s32*)(record + 1);
    destination.y = *(const u16*)((const u8*)record + 6);
    destination_ptr = &destination;
    destination.w = *(const volatile s32*)(record + 2);
    destination.h = *(const u16*)((const u8*)record + 10);
    record_byte_offset += 12;
    LoadImage(destination_ptr, (u32*)(source + record_byte_offset));
    DrawSync(0);
}

/* OPNTEX flag bit 3 adds a one-row preliminary upload before the main_entrypoint */
/* rectangle. The offset at +8 selects the main_entrypoint rectangle record.     */
