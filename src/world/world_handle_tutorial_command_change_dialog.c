#include "psx/types.h"

extern u8* g_world_threads;
extern u8* g_world_tutorial_command_ptr;

extern s32 world_get_is_text_printing(s32 thread_id);
extern void world_store_thread_function_parameters(s32 thread_id, s32 first, s32 second, s32 third);

/* Tutorial command: replace the dialog text once the current text has
 * finished printing. Operands: two message-id bytes (little-endian, biased
 * by 0xB800) that are handed to the text thread as its second parameter.
 *
 * -O0, like the neighbouring tutorial handlers. The message id is summed as
 * pointer arithmetic on purpose: written as plain integer addition, GCC
 * 2.6.3's fold re-associates `hi + (lo + 0xB800)` into `(hi + 0xB800) + lo`,
 * and the target adds the bias to the low byte first. */
void world_handle_tutorial_command_change_dialog(void) {
    if (world_get_is_text_printing(0x10) != 1) {
        world_store_thread_function_parameters(
            0x10, 0x99,
            (s32)((u8*)(g_world_tutorial_command_ptr[2] * 0x100) + (g_world_tutorial_command_ptr[1] + 0xB800)),
            0);
        g_world_tutorial_command_ptr += 3;
        *(s32*)(g_world_threads + 0x404C) = 1;
    }
}
