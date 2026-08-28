#include "psx/types.h"

extern s32 g_active_graphics_buffer_index;
extern u8 g_wldcore_render_object_queue;
extern s32 g_wldcore_render_object_count;
extern u8 g_wldcore_aux_render_object_queue;
extern s32 g_wldcore_aux_render_object_count;
extern u8 g_wldcore_world_primitive_buffers;
extern u8 g_wldcore_ordering_tables;
extern u8 g_wldcore_aux_ordering_tables;
extern s32 D_800BB500;
extern void* g_wldcore_scratch_buffer;

extern void VSync(s32);
extern void DrawSync(s32);
extern void StoreImage(void*, void*);
extern void wldcore_set_display_rect(s32, void*);
extern void func_8006A9D8(void*);
extern void func_8006AE20(void*, void*, s32);
extern void func_8006B78C(void*);
extern void func_8006BF9C(void*);
extern void func_8006C108(void*);
extern void func_8006C248(void*);
extern void func_80080758(void*);
extern void func_8008CDF0(void);
extern void func_8008D51C(void*);
extern void func_8008F434(void);
extern void func_80092B04(void*);
extern void func_80092B1C(void);
extern void func_800E13E8(s32, s32, s32, void*);
extern s32 world_gs_get_active_buffer(void);
extern void func_800E1710(void);
extern void world_gs_draw_ot(void*);
extern void world_gs_clear_ot(s32, s32, void*);
extern void func_800E1A88(void*);

/* Initialize the WLDCORE world buffers, menu state, and runtime tables. */
void world_initialize_core(void) {
    u8 stack_data[8];
    s32 count;

    DrawSync(0);
    VSync(0);
    func_800E1710();
    count = world_gs_get_active_buffer();
    g_active_graphics_buffer_index = count;
    func_800E1A88(&g_wldcore_world_primitive_buffers + count * 0xE000);
    world_gs_clear_ot(0, 0, &g_wldcore_aux_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_80080758(&g_wldcore_aux_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_80092B04((void*)0x1F8003FC);
    func_8006A9D8(&g_wldcore_aux_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_8008D51C(&g_wldcore_aux_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_8008CDF0();
    func_8006AE20(&g_wldcore_aux_ordering_tables + g_active_graphics_buffer_index * 0x14,
        &g_wldcore_aux_render_object_queue,
        g_wldcore_aux_render_object_count);
    func_80092B1C();
    func_800E13E8(0, 0, 0, &g_wldcore_aux_ordering_tables + g_active_graphics_buffer_index * 0x14);
    world_gs_draw_ot(&g_wldcore_aux_ordering_tables + g_active_graphics_buffer_index * 0x14);
    DrawSync(0);
    wldcore_set_display_rect(g_active_graphics_buffer_index, stack_data);
    StoreImage(stack_data, g_wldcore_scratch_buffer);
    DrawSync(0);
    D_800BB500 = -1;
    world_gs_clear_ot(0, 0, &g_wldcore_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_8008F434();
    func_8006C248(&g_wldcore_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_8006B78C(&g_wldcore_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_8006BF9C(&g_wldcore_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_8006C108(&g_wldcore_ordering_tables + g_active_graphics_buffer_index * 0x14);
    func_8006AE20(&g_wldcore_ordering_tables + g_active_graphics_buffer_index * 0x14,
        &g_wldcore_render_object_queue,
        g_wldcore_render_object_count);
    world_gs_draw_ot(&g_wldcore_ordering_tables + g_active_graphics_buffer_index * 0x14);
    DrawSync(0);
}
