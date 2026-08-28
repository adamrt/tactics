#include "psx/types.h"

extern u32 g_game_loop_stack_pointer;

extern void main_shutdown_display_and_audio_for_game_reset(void);
extern void restore_game_loop_stack_pointer(u32* source);

void main_game_reset(void) {
    main_shutdown_display_and_audio_for_game_reset();
    restore_game_loop_stack_pointer(&g_game_loop_stack_pointer);
}
