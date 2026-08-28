#include "psx/types.h"

extern s32 equip_out_get_item_type_from_item_number(s32 item);
extern s32 equip_get_item_total_count(s32 item);
extern s32 func_801C7980(s32 item, s32 category);
extern void func_801C79D4(s32 item, s32 category);
extern void equip_remove_item_from_category_list(s32 item, s32 category);

void equip_rebuild_item_category_list(s32 category) {
    s32 i;
    s16 item;
    s32 type;
    s32 cat;

    for (i = 1; i < 0xFE; i++) {
        item = i;
        type = equip_out_get_item_type_from_item_number(item);
        cat = 0;
        if (type != 0) {
            cat = type - 1;
        }
        if (category == cat) {
            if (equip_get_item_total_count(item) != 0) {
                if (func_801C7980(i, category) == 0) {
                    func_801C79D4(i, category);
                }
            } else {
                equip_remove_item_from_category_list(i, category);
            }
        }
    }
}
