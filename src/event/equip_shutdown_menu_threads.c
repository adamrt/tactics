#include "psx/types.h"

extern void equip_set_thread_completion_parameters(s32);
extern void equip_toggle_event_thread_11(s32);
extern s32 D_801CE19C;
extern s32 D_801CE1C4;

/* EQUIP.OUT 001bf5bc - Signal completion for menu sub-threads 0xD, 0xA, 0xC,
 * reset the primary menu state and two book-keeping globals. */
void equip_shutdown_menu_threads(void) {
    equip_set_thread_completion_parameters(0xD);
    equip_set_thread_completion_parameters(0xA);
    equip_set_thread_completion_parameters(0xC);
    equip_toggle_event_thread_11(0);
    D_801CE1C4 = 0;
    D_801CE19C = 0;
}
