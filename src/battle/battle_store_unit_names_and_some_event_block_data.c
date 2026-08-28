#include "psx/types.h"

extern u16 g_option_submenu_state;
extern s32 D_80166060;
extern u8 D_80169220[];
extern s16 D_8014D08A;
extern s16 D_8014D042;
extern s16 g_battle_preview_target_unit_id;
extern s16 D_8014D066;

extern void func_801334A4(void);
extern s32 battle_check_thread_running_status(s32 thread_id);
extern void battle_thread_initialize(s32 thread_id, s32 entry);
extern void battle_store_thread_function_parameters(s32 thread_id, s32 p0, s32 p1,
    s32 p2);
extern void D_8013D704(void);

void battle_store_unit_names_and_some_event_block_data(s32 event_id, s32 unit_a,
    s32 unit_b) {
    if (g_option_submenu_state == 1) {
        return;
    }
    func_801334A4();
    D_80166060 = D_80169220[event_id];
    if (unit_a != 0xff) {
        D_8014D08A = (s16)unit_a;
        D_8014D042 = (s16)unit_a;
    }
    if (unit_b != 0xff) {
        g_battle_preview_target_unit_id = (s16)unit_b;
        D_8014D066 = (s16)unit_b;
    }
    if (battle_check_thread_running_status(2) == 0) {
        battle_thread_initialize(2, (s32)D_8013D704);
    }
    battle_store_thread_function_parameters(2, event_id, 0, 0);
}
