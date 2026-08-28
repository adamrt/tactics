#include "fft/data.h"
#include "psx/types.h"

extern item_data_t g_primary_item_data[];
extern s32 g_battle_action_state;

extern s32 battle_get_script_variable(s32 id);
extern s32 battle_set_script_variable(s32 id, s32 value);

s32 battle_add_price_of_item_4_to_total_gil(u8* unit, s32 total, u8 item_id) {
    s32 value;

    if (g_battle_action_state != 0) {
        return 0;
    }
    if (unit[5] & 0x30) {
        return 0;
    }
    if (item_id != 0) {
        total += g_primary_item_data[item_id].price >> 2;
    }
    value = battle_get_script_variable(0x2C) + total;
    if (value > 99999999) {
        value = 99999999;
    } else if (value < 0) {
        value = 0;
    }
    battle_set_script_variable(0x2C, value);
    return total;
}
