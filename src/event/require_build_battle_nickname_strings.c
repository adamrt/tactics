#include "psx/types.h"

extern u8* g_battle_text_pointer_8;
extern u8* get_battle_stats_pointer(s32 unit_id);

void require_build_battle_nickname_strings(void) {
    u8* output;
    s32 unit_id;

    output = g_battle_text_pointer_8;
    unit_id = 0;
    do {
        u8* unit = get_battle_stats_pointer(unit_id);
        s32 length = 0;

        do {
            u8 value = (unit + length)[0x12c];
            *output = value;
            if ((value & 0xfe) != 0xfe) {
                output++;
                if (length == 15) {
                    *output++ = 0xfe;
                }
            } else {
                output++;
                break;
            }
            length++;
        } while (length < 16);
        unit_id++;
    } while (unit_id < 21);
}
