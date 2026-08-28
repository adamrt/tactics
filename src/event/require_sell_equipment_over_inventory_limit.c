#include "fft/battle.h"
#include "fft/data.h"

extern battle_stats_t* get_battle_stats_pointer(s32 unit_id);
extern s32 get_total_equipment_quantity(u32 item_id, s32 include_equipped);
extern item_data_t* main_get_item_data_pointer(s32 item_id);
extern s32 get_script_variable(s32 variable);
extern void set_script_variable(s32 variable, s32 value);

s32 require_sell_equipment_over_inventory_limit(s32 unit_id) {
    battle_stats_t* unit;
    s32 sold_equipment;
    s32 equipment_slot;

    sold_equipment = 0;
    unit = get_battle_stats_pointer(unit_id);
    equipment_slot = 0;
    do {
        u8 item_id = unit->equipment[equipment_slot];
        s32 sale_value;

        if (item_id == 0)
            goto next_slot;
        if (item_id == 0xff)
            goto next_slot;
        if (get_total_equipment_quantity(item_id, 1) < 100)
            goto next_slot;

        unit->equipment[equipment_slot] = 0;
        sale_value = main_get_item_data_pointer(item_id)->price;
        sale_value /= 4;
        set_script_variable(0x2c, get_script_variable(0x2c) + sale_value);
        sold_equipment = 1;

    next_slot:
        equipment_slot++;
    } while (equipment_slot < 7);
    return sold_equipment;
}
