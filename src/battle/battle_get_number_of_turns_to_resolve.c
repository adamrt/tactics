#include "psx/types.h"

extern s32 D_8018F51C;

typedef struct TurnEntry {
    u8 raw;
    u8 pad;
    u16 turn;
} TurnEntry;

u32 battle_get_number_of_turns_to_resolve(s32 arg0, s32 arg1, TurnEntry* entries) {
    s32 count = 0;
    if (D_8018F51C == 9 && arg1 != 0) {
        arg1 += 1;
    }
    arg1 <<= 8;
    do {
        u32 raw = entries->raw;
        u32 flag = raw & 0x40;
        s32 turn;
        raw &= 0x1F;
        if (raw == 0x1F)
            return 0xFF;
        turn = (s32)entries->turn;
        if (turn >= arg1) {
            if (arg1 != turn)
                return count & 0xFF;
            if (arg0 == (s32)raw && flag != 0)
                return count & 0xFF;
            if ((s32)raw >= arg0)
                return count & 0xFF;
            if (flag == 0)
                return count & 0xFF;
        }
        count++;
        entries++;
    } while (count < 0x28);
    return 0xFF;
}
