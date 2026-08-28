#include "psx/types.h"

extern void FntPrint(const char* format, ...);
extern void switch_to_next_event_thread(void);
extern const char D_8012D8C0[];
extern s16 D_80165FF4;

void battle_event_instruction_0x72(void) {
    FntPrint(D_8012D8C0);
    switch_to_next_event_thread();
    D_80165FF4 = 1;
}
