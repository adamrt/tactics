#include "psx/types.h"

extern s32 g_world_selected_proposition_id;
extern s32 g_world_proposition_picture_id;
extern s32 g_active_graphics_buffer_index;
extern void SetDispMask(s32);
extern s32 func_80068A68(s32);
extern void func_800686C8(void);
extern s32 world_gs_get_active_buffer(void);
extern void func_800E1A88(void*);
extern void world_initialize_core(void);
extern void VSync(s32);
extern void ResetGraph(s32);
extern void world_gs_clear_ot(s32, s32, void*);
extern void func_8006A018(s32);
extern void func_800E1710(void);

extern u8 g_wldcore_world_primitive_buffers;
extern u8 g_wldcore_aux_ordering_tables;
extern u8 g_wldcore_ordering_tables;

/* Initialize runtime tables and graphics state used by WLDCORE.
 * The matched range includes the jr delay slot at 0x800683f8. */
void world_initialize_runtime_state(void) {
    volatile s32 reserved_stack_words[2];
    s32 count;
    SetDispMask(0);
    g_world_proposition_picture_id = func_80068A68(g_world_selected_proposition_id);
    func_800686C8();
    count = world_gs_get_active_buffer();
    g_active_graphics_buffer_index = count;
    func_800E1A88(&g_wldcore_world_primitive_buffers + count * 0xE000);
    world_initialize_core();
    VSync(0);
    ResetGraph(1);
    world_gs_clear_ot(0, 0, &g_wldcore_aux_ordering_tables + g_active_graphics_buffer_index * 0x14);
    world_gs_clear_ot(0, 0, &g_wldcore_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_8006A018(0);
    func_800E1710();
    SetDispMask(0);
}
