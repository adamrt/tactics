#include "psx/types.h"

extern u32 g_game_loop_stack_pointer;

extern void main_startup(void);
extern void store_stack_pointer(u32* destination);
extern void main_game_loop(void);
extern void PadStop(void);
extern void StopCallback(void);

void main(void) {
    main_startup();
    store_stack_pointer(&g_game_loop_stack_pointer);
    main_game_loop();
    PadStop();
    StopCallback();
}
