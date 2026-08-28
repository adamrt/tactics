#include "psx/types.h"

extern s32 g_system_flags;
extern s32 g_active_graphics_buffer_index;
extern u8 g_cd_file_state;
extern u8 g_wldcore_world_primitive_buffers;

extern s32 func_8006858C(void);
extern void world_initialize_subsystems(void);
extern void func_80069400(s32, s32);
extern void open_file_to_ram_center(void*);
extern void func_80090E20(void);
extern s32 world_gs_get_active_buffer(void);
extern void func_800E1A88(void*);
extern void func_800694A8(void);
extern void func_8008CF14(void);
extern void wldcore_bar_menu_idle_routine(void);
extern void world_process_frame_gate(void);
extern void func_800677A4(void);
extern void func_80067A78(void);
extern void SetDispMask(s32);
extern void tick(void);
extern void world_finalize_loop(void);

/* WLDCORE's entrypoint; the overlay is loaded at 0x80067000. */
s32 world_bin_entrypoint(void) {
    s32 count;

    for (;;) {
        if (func_8006858C() != 0) {
            return 0;
        }
        world_initialize_subsystems();
        func_80069400(0, 0x10);
        for (;;) {
            if ((g_system_flags & 1) == 0) {
                break;
            }
            open_file_to_ram_center(&g_cd_file_state);
            func_80090E20();
            count = world_gs_get_active_buffer();
            g_active_graphics_buffer_index = count;
            func_800E1A88(&g_wldcore_world_primitive_buffers + count * 0xE000);
            func_800694A8();
            func_8008CF14();
            wldcore_bar_menu_idle_routine();
            world_process_frame_gate();
            if (g_system_flags & 2) {
                func_800677A4();
            } else {
                func_80067A78();
            }
            if (g_system_flags & 0x40) {
                SetDispMask(0);
            } else {
                SetDispMask(1);
            }
            tick();
        }
        if (g_system_flags & 0x10000) {
            continue;
        }
        world_finalize_loop();
        {
            s32 flags = g_system_flags;

            if (flags & 0x10000000) {
                return 5;
            }
            if (flags & 0x02000000) {
                return 4;
            }
            if (flags & 0x200000) {
                return 2;
            }
            {
                s32 display_mask;

                if (flags & 0x40000) {
                    display_mask = 2;
                    goto return_display_mask;
                }
                display_mask = (flags & 0x8000) > 0;
            return_display_mask:
                return display_mask;
            }
        }
    }
}
