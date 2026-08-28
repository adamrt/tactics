#include "psx/types.h"

extern s16 D_801E9100;
extern s16 g_equip_poly_ft4_capacity;
extern s16 g_equip_line_f2_capacity;
extern s16 g_equip_tile_capacity;
extern s16 g_equip_draw_move_capacity;
extern s16 D_801E9104;
extern s16 D_801E9224;
extern s16 D_801E9068;
extern s16 D_801E90A8;
extern s16 g_equip_poly_f4_capacity;
extern s16 D_801E906C;
extern s16 D_801E90B0;
extern s16 D_801E9074;
extern s16 D_801E90C0;
extern s16 D_801E9098;
extern s16 D_801E90A0;
extern s16 D_801E9094;
extern s16 D_801E909C;
extern s16 D_801E90A4;
extern s16 D_801E924C;
extern s16 D_801E92D4;
extern s16 D_801E92F8;
extern s16 D_801E908C;
extern s16 D_801E90E4;
extern s16 D_801E90FC;
extern s32 D_801CE180;
extern void* D_80173ff8;
extern u8 D_801CE0E0[];
extern u8 D_801E0B9C[];
extern u8 D_801E099C[];
extern u8 D_801D87EC[];
extern u8 D_801E1044[];
extern u8 D_801E1184[];
extern u8 D_801E04EC[];
extern u8 D_801E08AC[];
extern u8 D_801E0D74[];

extern void func_801CDA80(void*, void*, s32, s32, s32, void*, s32, s32,
    s32, s32, void*, s32, s32, s32, s32, s32, void*,
    s32, s32, s32, s32, s32, s32, void*, void*, void*);
extern void equip_load_unit_data_from_battle_stats(s32);
extern void equip_load_menu_images_and_reset_lists(void);
extern void equip_load_selected_unit_data(void);
extern void equip_toggle_event_thread_13(s32);
extern void equip_toggle_event_threads_10_and_12(s32);
extern void equip_toggle_event_thread_12(s32);

void equip_initialize_screen(s32 arg0) {
    D_801E9100 = 0x40;
    g_equip_poly_ft4_capacity = 0x190;
    g_equip_line_f2_capacity = 0xA;
    g_equip_tile_capacity = 0xA;
    g_equip_draw_move_capacity = 0x14;
    D_801E9104 = 6;
    D_801E9224 = 0x1E;
    D_801E9068 = 0;
    D_801E90A8 = 0;
    g_equip_poly_f4_capacity = 0;
    D_801E906C = 0;
    D_801E90B0 = 0;
    D_801E9074 = 0;
    D_801E90C0 = 0;
    D_801E9098 = 0;
    D_801E90A0 = 0;
    D_801E9094 = 0;
    D_801E909C = 0;
    D_801E90A4 = 0;
    D_801E924C = 0;
    D_801E92D4 = 0;
    D_801E92F8 = 0;
    D_801E908C = 0;
    D_801E90E4 = 0;
    D_801E90FC = 0;
    func_801CDA80(D_801E0B9C, D_801E099C, 0, 0, 0, D_801D87EC, 0, 0, 0, 0,
        D_801E1044, 0, 0, 0, 0, 0, D_801E1184, 0, 0, 0, 0, 0, 0,
        D_801E04EC, D_801E08AC, D_801E0D74);
    equip_load_unit_data_from_battle_stats(arg0);
    equip_load_menu_images_and_reset_lists();
    D_801CE180 = arg0;
    D_80173ff8 = D_801CE0E0;
    equip_load_selected_unit_data();
    equip_toggle_event_thread_13(1);
    equip_toggle_event_threads_10_and_12(1);
    equip_toggle_event_thread_12(1);
}
