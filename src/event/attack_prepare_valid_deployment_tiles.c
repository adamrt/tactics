#include "psx/types.h"

extern u8 g_attack_deployment_tile_buffer[];
extern s32 g_attack_deployment_arrow_position_mode;
extern s32 g_attack_deployment_menu_state;
extern s32 D_801cd074;
extern s32 D_801cd078;
extern s32 D_801cd07c;
extern s32 D_801cd080;

extern void initialize_event_thread(s32 thread_id, void (*entrypoint)(void));
extern void battle_store_thread_function_parameters(s32 thread_id, s32 value0,
    s32 value1, s32 value2);
extern void func_801c67cc(void);
extern void func_801c7288(void* data);

void attack_prepare_valid_deployment_tiles(void) {
    D_801cd080 = 1;
    g_attack_deployment_menu_state = 5;
    D_801cd074 = 0;
    D_801cd078 = 0;
    D_801cd07c = 0;
    g_attack_deployment_arrow_position_mode = 0;
    func_801c7288(g_attack_deployment_tile_buffer);
    initialize_event_thread(15, func_801c67cc);
    battle_store_thread_function_parameters(15, 0, 0, 0);
}
