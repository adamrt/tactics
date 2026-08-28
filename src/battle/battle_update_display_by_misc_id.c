#include "psx/types.h"

extern void* battle_get_unit_misc_data_by_misc_id(u16);
extern void update_unit_display(void*);

void battle_update_display_by_misc_id(u16 misc_id) {
    update_unit_display(battle_get_unit_misc_data_by_misc_id(misc_id));
}
