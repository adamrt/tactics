#include "fft/battle.h"
#include "psx/types.h"

extern void func_8006DC8C(battle_misc_data_t*);

void battle_transfer_target_coordinates(battle_misc_data_t* src, battle_misc_data_t* dst) {
    dst->movement.bytes.destination_x = src->target_new_x;
    dst->movement.bytes.destination_y = src->target_new_y;
    dst->movement.bytes.destination_z = src->target_new_map_level;
    func_8006DC8C(dst);
}
