#include "psx/types.h"

extern s32 g_companion_executable_request_index;

/* Queues companion executable 8 for loading without waiting for the current
 * request to drain (compare battle_setup_open_companion_executable, which blocks).
 * The poll at 0x8013d19c drives it to completion. */
void battle_request_companion_executable_8(void) {
    g_companion_executable_request_index = 8;
}
