#include "psx/types.h"

extern void battle_acting_unit_vector_normal(void);
extern s32 g_battle_current_vector_x[1];
extern s32 g_battle_current_vector_z;
extern s32 g_battle_current_vector_y;

void battle_acting_unit_vector_shift(void) {
    battle_acting_unit_vector_normal();
    g_battle_current_vector_x[0] *= 2;
    g_battle_current_vector_z *= 2;
    g_battle_current_vector_y *= 2;
}
