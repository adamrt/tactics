#include "fft/battle.h"
#include "psx/types.h"

typedef struct BattleCoordShort {
    u16 x;
    u16 z;
    u16 y;
} BattleCoordShort;

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void main_pointer_exception_handler(s32 error_code);

/* The target contains two separately addressable copies of this accumulator. */
s32 battle_increment_another_coords_by_misc_id_copy(
    u32 misc_id, const BattleCoordShort* amount) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    if (unit != 0) {
        unit->effect_vector_2_x = unit->effect_vector_2_x + amount->x;
        unit->effect_vector_2_z = unit->effect_vector_2_z + amount->z;
        unit->effect_vector_2_y = unit->effect_vector_2_y + amount->y;
    } else {
        main_pointer_exception_handler(12);
        return 0;
    }
    return 1;
}
