#include "psx/types.h"

typedef struct TextReader {
    /* 0x00 */ u8 unk_00[0x14];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1c */ u8* unk_1C;
} TextReader;

u8* battle_find_next_text_character(TextReader* reader, u8* p) {
    s32 count;
    u8 c;

    count = reader->unk_18;
    p += 1;
    if (count > 0) {
        count -= 1;
        reader->unk_18 = count;
        if (count == 0) {
            p = reader->unk_1C;
            reader->unk_1C = (u8*)-1;
        }
    }
    c = p[0];
    if (((c & 0xF0) == 0xF0) && ((c & 0xF) < 4)) {
        reader->unk_1C = p + 3;
        reader->unk_14 = (p[0] & 3) * 8;
        reader->unk_18 = p[1] >> 5;
        reader->unk_18 = reader->unk_18 + reader->unk_14 + 4;
        reader->unk_14 = (p[1] & 0xF) * 254;
        reader->unk_14 = p[2] + reader->unk_14;
        p -= reader->unk_14;
    }
    return p;
}
