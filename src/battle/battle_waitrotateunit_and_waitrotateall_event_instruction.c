#include "psx/types.h"

extern u8 D_8016D9DC[][7];

extern void switch_to_next_thread(void);
extern s32 func_80133158(s32);

void battle_waitrotateunit_and_waitrotateall_event_instruction(s32 unit_id) {
    s32 i;
    s32 index;

    if (unit_id == -1) {
        do {
            switch_to_next_thread();
            for (i = 0; i < 0x15; i++) {
                if (D_8016D9DC[i][0] != 0) {
                    break;
                }
            }
        } while (i != 0x15);
    } else {
        index = func_80133158(unit_id);
        if (index != 0x7D0) {
            do {
                switch_to_next_thread();
            } while (D_8016D9DC[index][0] != 0);
        }
    }
}
