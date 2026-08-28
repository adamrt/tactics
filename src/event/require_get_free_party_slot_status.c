#include "psx/types.h"

extern u8* get_battle_stats_pointer(s32 unit_id);
extern u8* main_get_party_data_pointer(s32 party_index);
extern s32 main_find_free_party_slot(s32 save_formation, u8* palette);

s32 require_get_free_party_slot_status(s32 unit_id) {
    u8* party;
    s32 index;

    if (get_battle_stats_pointer(unit_id)[6] & 1) {
        return 2;
    }

    index = 0;
    do {
        party = main_get_party_data_pointer(index);
        if ((party[1] != 0xff) && (party[0] != 0) && (party[0] < 4)) {
            break;
        }
        index++;
    } while (index < 20);

    return main_find_free_party_slot(0, party + 3) != -1;
}
