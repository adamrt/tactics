#include "psx/types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} EquipRect;

extern void* g_battle_text_pointers;
extern u16 D_801CE1E8[];
extern s32 g_equip_help_message_id;
extern void equip_load_image_and_wait(EquipRect*, void*);
extern void equip_store_image_and_wait(EquipRect*, void*);
extern void equip_clear_menu_indices(void);
extern void equip_reset_selection_indices(void);
extern void equip_build_item_inventory_totals(void);
extern void equip_rebuild_item_category_list(s32);
extern void equip_clear_all_indexed_action_records(void);

void equip_load_menu_images_and_reset_lists(void) {
    EquipRect rect;
    u16 buf1[4];
    u16 buf2[12];

    rect.x = 0x100;
    rect.y = 0;
    rect.w = 0x40;
    rect.h = 0x30;
    equip_load_image_and_wait(&rect, g_battle_text_pointers);
    rect.x = 0x100;
    rect.y = 0xFA;
    rect.w = 0x40;
    rect.h = 4;
    equip_load_image_and_wait(&rect, D_801CE1E8);
    rect.x = 0x3C0;
    rect.y = 0x1F0;
    rect.w = 0x10;
    rect.h = 1;
    equip_store_image_and_wait(&rect, buf1);
    buf2[0] = 0;
    rect.x = 0x120;
    rect.y = 0xFE;
    rect.w = 0x10;
    rect.h = 1;
    equip_load_image_and_wait(&rect, buf1);
    rect.x = 0x100;
    rect.y = 0xFE;
    rect.w = 0xC;
    rect.h = 1;
    equip_load_image_and_wait(&rect, buf2);
    rect.x = 0x3C0;
    rect.y = 0x1F4;
    rect.w = 0x10;
    rect.h = 1;
    equip_store_image_and_wait(&rect, buf1);
    buf2[0] = 0;
    rect.x = 0x130;
    rect.y = 0xFE;
    rect.w = 0x10;
    rect.h = 1;
    equip_load_image_and_wait(&rect, buf1);
    rect.x = 0x110;
    rect.y = 0xFE;
    rect.w = 0xC;
    rect.h = 1;
    equip_load_image_and_wait(&rect, buf2);
    equip_clear_menu_indices();
    g_equip_help_message_id = 0;
    equip_reset_selection_indices();
    equip_build_item_inventory_totals();
    equip_rebuild_item_category_list(0);
    equip_rebuild_item_category_list(1);
    equip_rebuild_item_category_list(2);
    equip_rebuild_item_category_list(3);
    equip_rebuild_item_category_list(4);
    equip_clear_all_indexed_action_records();
}
