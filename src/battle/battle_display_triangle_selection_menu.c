#include "psx/types.h"

extern void battle_set_thread_task_id(s32);
extern s32 battle_is_battle_camera_active(void);
extern void func_8014CA80(void);
extern void battle_80142bd0(s32);
extern void func_80138ED8(void);
extern u16 D_8016604A;
extern s32 D_80166044;

void battle_display_triangle_selection_menu(void) {
    battle_set_thread_task_id(0x42);
    while (battle_is_battle_camera_active() != 0 || D_8016604A != 0) {
        func_8014CA80();
    }
    battle_80142bd0(0xFE);
    D_80166044 = 0;
    func_80138ED8();
}
