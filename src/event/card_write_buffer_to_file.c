#include "psx/types.h"

extern s32 g_card_open_descriptor;

extern s32 card_open_selected_file_with_retries(const char* filename, s32 mode);
extern s32 card_close_file_with_retries(s32 descriptor);
extern s32 card_seek_file_with_retries(s32 descriptor, s32 offset, s32 origin);
extern s32 FileGetError(s32 descriptor);
extern s32 FileWrite(s32 descriptor, const void* source, s32 size);

s32 card_write_buffer_to_file(const char* filename, const u8* source, s32 size,
    s32 create_file) {
    s32 error;
    s32 result;
    s32 retries;
    s32 total_written;

    if (create_file != 0) {
        result = card_open_selected_file_with_retries(
            filename, ((u32)source[3] << 16) | 0x200);
        if (result <= -1) {
            return -1;
        } else {
            if (card_close_file_with_retries(g_card_open_descriptor) == 0) {
                return -1;
            }
            result = card_open_selected_file_with_retries(filename, 2);
            if (result <= -1) {
                return -1;
            }
        }
        create_file = 0;
    } else {
        result = card_open_selected_file_with_retries(filename, 2);
        if (result < 0) {
            return -1;
        }
    }

    error = FileGetError(g_card_open_descriptor);
    if (error != 0) {
        card_close_file_with_retries(g_card_open_descriptor);
        return -1;
    }

    total_written = 0;
    retries = 0;
    while (retries < 40) {
        if (card_seek_file_with_retries(g_card_open_descriptor, total_written,
                1)
            < 0) {
            break;
        }

        result = FileWrite(g_card_open_descriptor, source + total_written,
            size - total_written);
        if (result != -1) {
            total_written += result;
            if ((u32)total_written >= (u32)size) {
                break;
            }
        }
        retries++;
    }

    if (card_close_file_with_retries(g_card_open_descriptor) == 0) {
        return -1;
    }
    if (result != size) {
        result = -1;
    }
    return total_written;
}
