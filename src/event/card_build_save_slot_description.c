#include "psx/types.h"

extern u8 g_card_text_data[];
extern const u8 g_card_job_name_text[];
extern const u8 g_card_location_name_text[];

typedef struct CardSaveBufferDescriptionFields {
    u8 unknown_000[0x101];
    u8 name[0x11];
    u8 field_112;
    u8 field_113;
    u8 field_114;
    u8 field_115;
    u8 field_116;
} CardSaveBufferDescriptionFields;

extern CardSaveBufferDescriptionFields* g_card_save_buffer_pointer;

extern const u8* card_advance_encoded_string_segments(const u8* text,
    s32 count, s32 mode);

void card_build_save_slot_description(s32 mode, u8* destination) {
    s32 index;
    volatile u8 stack_padding[4];
    const u8* source;

    if (mode == 1) {
        source = card_advance_encoded_string_segments(g_card_text_data, 14, 1);
        while ((*destination++ = *source++) != 0xfe) {
        }
    } else if (mode == 0) {
        index = 0;
        while (g_card_save_buffer_pointer->name[index] != 0xfe) {
            *destination++ = g_card_save_buffer_pointer->name[index];
            index++;
        }

        *destination++ = 0xe7;
        *destination++ = 0x58;
        source = card_advance_encoded_string_segments(
            g_card_job_name_text, g_card_save_buffer_pointer->field_112, 1);
        while (*source != 0xfe) {
            *destination++ = *source++;
        }

        *destination++ = 0xe7;
        *destination++ = 0xac;
        source = card_advance_encoded_string_segments(g_card_text_data, 13, 1);
        while (*source != 0xfe) {
            *destination++ = *source++;
        }

        *destination++ = g_card_save_buffer_pointer->field_113 / 10;
        *destination++ = g_card_save_buffer_pointer->field_113 % 10;
        *destination++ = 0xfe;
        source = card_advance_encoded_string_segments(
            g_card_text_data, g_card_save_buffer_pointer->field_114, 1);
        while (*source != 0xfe) {
            *destination++ = *source++;
        }

        *destination++ = 0xfa;
        *destination++ = g_card_save_buffer_pointer->field_115 / 10;
        *destination++ = g_card_save_buffer_pointer->field_115 % 10;
        *destination++ = 0xe7;
        *destination++ = 0x58;
        source = card_advance_encoded_string_segments(
            g_card_location_name_text, g_card_save_buffer_pointer->field_116, 1);
        while ((*destination++ = *source++) != 0xfe) {
        }
    }
    *destination = 0xfe;
}
