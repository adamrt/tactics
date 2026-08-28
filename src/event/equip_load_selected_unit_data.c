#include "psx/types.h"

extern u8 g_equip_selected_unit_index;
extern u8* g_equip_unit_data[];
extern u8 D_801CE424[];
extern u8 D_801CE46C[];
extern u8 D_801CE48C[];
extern void bcopy(const void* source, void* destination, u32 size);
extern void equip_sum_equipment_stat_bonuses(void* dst, void* src);
extern void equip_copy_unit_data_to_compare_slot();
extern void equip_reset_menu_state_flags(void);

void equip_load_selected_unit_data(void) {
    u8 unused[0x80];
    u8* unit;

    unit = g_equip_unit_data[g_equip_selected_unit_index];
    if (*(s16*)(unit + 0x10) < *(s16*)(unit + 0xC)) {
        *(s16*)(unit + 0xC) = *(s16*)(unit + 0x10);
    }

    unit = g_equip_unit_data[g_equip_selected_unit_index];
    if (*(s16*)(unit + 0x16) < *(s16*)(unit + 0x12)) {
        *(s16*)(unit + 0x12) = *(s16*)(unit + 0x16);
    }

    bcopy(g_equip_unit_data[g_equip_selected_unit_index], D_801CE424, 0x22);
    bcopy(g_equip_unit_data[g_equip_selected_unit_index] + 0x22, D_801CE46C, 0xE);
    bcopy(g_equip_unit_data[g_equip_selected_unit_index] + 0x30, D_801CE48C, 0x40);
    equip_sum_equipment_stat_bonuses(D_801CE48C, g_equip_unit_data[g_equip_selected_unit_index] + 0x54);
    equip_copy_unit_data_to_compare_slot(g_equip_selected_unit_index, 1);
    equip_reset_menu_state_flags();
}
