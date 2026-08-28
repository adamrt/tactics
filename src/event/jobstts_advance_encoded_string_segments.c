#include "fft/text.h"
#include "psx/types.h"

const u8* jobstts_advance_encoded_string_segments(const u8* text,
    s16 terminators) {
    while (terminators != 0) {
        u8 character = *text++;

        if (character >= TEXT_EXTENDED_GLYPH_PREFIX_FIRST) {
            if (character <= TEXT_EXTENDED_GLYPH_PREFIX_LAST) {
                text++;
            } else if (character >= TEXT_END_WAIT_FOR_CONFIRM) {
                terminators--;
            }
        }
    }
    return text;
}
