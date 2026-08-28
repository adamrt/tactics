#include "psx/gpu.h"

typedef struct {
    RECT rect;
    u16 unk_8;
    u16 unk_A;
} EquipIconRect;

extern EquipIconRect D_801E8CC4;
extern s16 g_equip_item_list_entries[];
extern u16 D_801E90D0;
extern u16 D_801D86BA;

extern s32 equip_get_item_type(s32 item);
extern void equip_get_item_type_icon_rect(s32 index, RECT* output);

/* EQUIP.OUT 001c41dc - Build the icon rect for the item in menu slot `index`. */
EquipIconRect* equip_build_item_row_icon_rect(s32 index) {
    EquipIconRect* out = &D_801E8CC4;
    equip_get_item_type_icon_rect(equip_get_item_type(g_equip_item_list_entries[index]), &out->rect);
    out->unk_8 = D_801E90D0;
    out->unk_A = D_801D86BA;
    return out;
}
