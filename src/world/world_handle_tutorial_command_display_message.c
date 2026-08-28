#include "psx/types.h"

extern void world_initialize_thread(s32 id, void (*entry)(void));
extern void world_store_thread_function_parameters(s32 id, s32 a, s32 b, s32 c);
extern void func_800e4d9c(void);
extern u8* g_world_tutorial_command_ptr;
extern u8* g_world_threads;

/* Tutorial command: start the text thread on a new message. Operands: two
 * message-id bytes (little-endian, biased by 0xB800) and a third byte stored
 * into the thread block at +0x405C.
 *
 * -O0, like the neighbouring tutorial handlers. The message id is summed as
 * pointer arithmetic on purpose: written as plain integer addition, GCC
 * 2.6.3's fold re-associates `hi + (lo + 0xB800)` into `(hi + 0xB800) + lo`,
 * and the target adds the bias to the low byte first. */
void world_handle_tutorial_command_display_message(void) {
    world_initialize_thread(0x10, func_800e4d9c);
    world_store_thread_function_parameters(
        0x10, 0x99,
        (s32)((u8*)(g_world_tutorial_command_ptr[2] * 0x100) + (g_world_tutorial_command_ptr[1] + 0xB800)),
        0);
    *(s32*)(g_world_threads + 0x405C) = g_world_tutorial_command_ptr[3];
    g_world_tutorial_command_ptr += 4;
}
