#include "psx/types.h"

typedef struct {
    /* 0x00 */ u8 unk00[0x28];
    /* 0x28 */ void (*func)(void);
} BunitThreadDesc;

extern u8 g_bunit_menu_thread_running;
extern BunitThreadDesc* g_menu_descriptor;
extern s32 battle_check_thread_r4_running_status(s32 id);
extern void battle_thread_initialize(s32 id, void (*func)(void));
extern void battle_store_thread_function_parameters(s32 id, void* a1, s32 a2, s32 a3);

u8 bunit_run_menu_descriptor_thread(s32 id, BunitThreadDesc* desc) {
    if (g_bunit_menu_thread_running == 0) {
        if (battle_check_thread_r4_running_status(id) != 0) {
            return 1;
        }
        g_menu_descriptor = desc;
        battle_thread_initialize(id, desc->func);
        battle_store_thread_function_parameters(id, g_menu_descriptor, 0, 0);
        g_bunit_menu_thread_running = 1;
    }
    g_bunit_menu_thread_running = battle_check_thread_r4_running_status(id);
    return g_bunit_menu_thread_running;
}
