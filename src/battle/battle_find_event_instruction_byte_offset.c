#include "psx/types.h"

extern u8 D_8014D170;

s32 battle_find_event_instruction_byte_offset(s32 offset, s32 opcode) {
    u8* base = *(u8**)0x80173CA4;
    s32 tmp;
    u8 op;
    for (;;) {
        op = base[offset];
        if (op == 0xDB)
            return 0;
        if (op == opcode)
            return offset;
        tmp = offset + 1;
        offset = tmp + (&D_8014D170)[op];
    }
}
