#include "psx/types.h"

extern s32 battle_return_one(s32 arg0);
extern void switch_to_next_thread(void);

void battle_return_1_with_extra_steps_0x14a4d8(s32 arg0) {
    while (battle_return_one(arg0) == 0) {
        switch_to_next_thread();
    }
}
