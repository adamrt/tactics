#include "psx/types.h"

extern s32 LoadImage();
extern s32 allocate_battle_memory();
extern s32 battle_free_battle_memory();
extern s32 get_script_variable();
extern s32 main_get_dat_as_wd();
extern s32 (*g_call_inner_subroutine_target)();
extern s32 call_inner_subroutine();
extern s32 g_attack_map_title_image_rect;
extern s32 g_attack_map_title_palette_rect;
extern s32 g_attack_map_title_palette_data;

void attack_load_map_title_graphic(void) {
    s32 group;
    s32 image;
    s32 title;
    s32 adjusted;
    s32 group_input;

    image = allocate_battle_memory(0x2800);
    title = get_script_variable(0x33);
    adjusted = title - 1;
    group_input = adjusted;
    if (adjusted < 0) {
        group_input = title + 2;
    }
    group_input = (group = group_input >> 2);
    group = adjusted - group * 4;

    if (adjusted != 0xff) {
        title = group_input * 5 + 0xdac;
        g_call_inner_subroutine_target = main_get_dat_as_wd;
        call_inner_subroutine(title, 0x2800, image);
    }

    LoadImage(&g_attack_map_title_image_rect, image + group * 0xa00);
    LoadImage(&g_attack_map_title_palette_rect, &g_attack_map_title_palette_data);
    battle_free_battle_memory(image);
}
