#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u8 g_wldcore_opcode_operand_byte;
extern s16 D_800D4854;
extern void world_initialize_thread(s32 thread_id, void (*entry)(void));
extern void world_store_thread_function_parameters(
    s32 thread_id, s32 function_index, s32 parameter_0, s32 parameter_1);
extern void func_800e4d9c(void);

void wldcore_opcode_start_script_thread_flags_04(void) {
    s32 operand;

    operand = g_wldcore_opcode_operand_byte;
    world_initialize_thread(14, func_800e4d9c);
    world_store_thread_function_parameters(14, 9, operand | 0x8800, 0);
    D_800D4854 = operand;
    g_wldcore_state_flags |= 4;
}
