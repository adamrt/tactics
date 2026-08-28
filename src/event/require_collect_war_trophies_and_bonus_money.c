#include "psx/types.h"

typedef struct WarResult {
    u8 item_ids[0x15];
    u8 item_count;
    u8 padding[2];
    s32 bonus_money;
} WarResult;
typedef struct Item {
    u8 unknown_00[8];
    u16 price;
} Item;
extern WarResult g_require_war_trophy_search_result;
extern u8 g_require_war_trophy_item_count;
extern s32 g_require_war_trophy_entry_types[];
extern s32 g_require_war_trophy_entry_values[];
extern s32 g_require_war_trophy_entry_count;
extern u8 g_available_item_quantities[];
extern void find_war_trophies_and_bonus_money(WarResult* result);
extern s32 get_total_equipment_quantity(s32 item_id, s32 include_equipped);
extern Item* main_get_item_data_pointer(s32 item_id);
extern s32 get_script_variable(s32 variable);
extern void set_script_variable(s32 variable, s32 value);

void require_collect_war_trophies_and_bonus_money(void) {
    s32 i;
    s32 item_id;
    s32 quantity;
    s32 price;
    s32 adj;
    s32 funds;
    s32 n;
    Item* item;
    u8* qp;
    volatile u32 pad[4];
    s32* iv;
    s32* it;

    g_require_war_trophy_entry_count = 0;
    find_war_trophies_and_bonus_money(&g_require_war_trophy_search_result);

    {
        s32 j;
        s32 next;
        iv = g_require_war_trophy_entry_values;
        it = g_require_war_trophy_entry_types;
        j = g_require_war_trophy_entry_count;
        iv[j] = g_require_war_trophy_search_result.bonus_money;
        it[j] = 1;
        if (iv[j] != 0) {
            next = j + 1;
            g_require_war_trophy_entry_count = next;
        }
    }

    i = 0;
    n = g_require_war_trophy_item_count;
    if (n > 0) {
        s32* tb;
        s32* vb = iv;
        u8* cp;
        s32 e;
        s32 loop_count;
        tb = it;
        cp = &g_require_war_trophy_search_result.item_count;
        do {
            e = g_require_war_trophy_entry_count;
            item_id = g_require_war_trophy_search_result.item_ids[i];
            i++;
            vb[e] = item_id;
            tb[e] = 0;
            loop_count = *cp;
            g_require_war_trophy_entry_count = e + 1;
        } while (i < loop_count);
    }

    i = 0;
    if (g_require_war_trophy_entry_count > 0) {
        s32* vp = g_require_war_trophy_entry_values;
        s32* tp = g_require_war_trophy_entry_types;
        register s32 limit __asm__("$2");
        do {
            if (*tp == 0) {
                item_id = *(u8*)vp;
                quantity = get_total_equipment_quantity(item_id, 1);
                if (quantity == 99) {
                    item = main_get_item_data_pointer(*vp);
                    price = item->price;
                    if (price < 0) {
                        adj = price + 3;
                    } else {
                        adj = price;
                    }
                    price = adj >> 2;
                    funds = get_script_variable(0x2c);
                    set_script_variable(0x2c, funds + price);
                } else {
                    s32 id = *vp;
                    qp = &g_available_item_quantities[id];
                    (*qp)++;
                }
            } else {
                funds = get_script_variable(0x2c);
                set_script_variable(0x2c, funds + *vp);
            }
            vp++;
            limit = g_require_war_trophy_entry_count;
            i++;
            tp++;
        } while (i < limit);
    }
}
