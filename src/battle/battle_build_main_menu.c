#include "psx/types.h"

extern s32 g_current_event_thread_id;
extern s16 g_selected_unit_index;
extern u8 D_8014D46C[];
extern s32 D_80169870[];
extern void func_80138ED8(s32 a, s32 b);
extern void* func_8014CBC0(void);
extern void battle_stop_current_thread(void);

void battle_build_main_menu(void) {
    u8* r;

    u8* p;
    r = func_8014CBC0();
    p = &D_8014D46C[g_selected_unit_index * 0x11];
    D_80169870[g_current_event_thread_id * 0x100] = 1;
    func_80138ED8(1, g_selected_unit_index);
    *p = r[0x38];
    battle_stop_current_thread();
}
