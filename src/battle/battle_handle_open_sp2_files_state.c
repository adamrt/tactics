#include "fft/battle.h"
#include "fft/battle_vram.h"
#include "psx/gpu.h"

extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void* game_malloc(s32);
extern void main_game_free(void*);
extern s32 open_sp2(battle_misc_data_t*, void*);
extern s32 main_check_file_still_loading(void);
extern void set_damage_display_type(void);
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32, s32);
extern void* g_sp2_data;
extern s32 g_controller_input_copy_1;

void battle_handle_open_sp2_files_state(void) {
    RECT image_rect;
    battle_misc_data_t* unit;
    s32 open_result;
    s32 counter;
    s32 empty_slot;
    s32 offset;
    RECT* image_rect_address;
    void* sp2_data;

    unit = battle_get_casting_unit_misc_data();
    if (g_sp2_data == 0) {
        g_sp2_data = game_malloc(0x8000);
        open_result = open_sp2(unit, g_sp2_data);
        if (open_result == -1) {
            main_game_free(g_sp2_data);
            g_sp2_data = 0;
            set_damage_display_type();
        } else if (open_result == 0) {
            main_game_free(g_sp2_data);
            g_sp2_data = 0;
        }
    } else if (main_check_file_still_loading() == 0) {
        counter = 0;
        empty_slot = 0xff;
        offset = 0;
        do {
            if (*(u32*)((u8*)g_battle_vram_slots + offset) == empty_slot) {
                image_rect_address = &image_rect;
                sp2_data = g_sp2_data;
                *(u32*)((u8*)g_battle_vram_slots + offset) = unit->unit_id | 0x40;
                image_rect_address->x = *(u16*)((u8*)&g_battle_vram_slots[0].image_rect.x + offset);
                image_rect_address->y = *(u16*)((u8*)&g_battle_vram_slots[0].image_rect.y + offset);
                image_rect_address->w = 0x40;
                image_rect_address->h = 0x100;
                LoadImage(image_rect_address, sp2_data);
                set_damage_display_type();
                break;
            }
            counter++;
            offset += 0x7564;
        } while (counter < 2);
    }
    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
}
