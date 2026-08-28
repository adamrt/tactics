#include "fft/battle.h"
#include "psx/types.h"

extern s32 D_800E4E74;
extern s32 D_800E4E78;
extern s32 D_800E4E7C;
extern s32 D_800A1C48;
extern s32 D_800A1C4C;

extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void func_8001C068(s32*, s32*);

void battle_acting_unit_vector_normal(void) {
    s32 v[3];
    battle_misc_data_t* unit;

    unit = battle_get_source_unit_misc_data();
    v[0] = unit->screen_x - D_800E4E74 / 4096;
    v[1] = unit->screen_z - D_800E4E78 / 4096;
    v[2] = unit->screen_y - D_800E4E7C / 4096;
    func_8001C068(v, &D_800A1C48);
    D_800A1C4C = D_800A1C4C << 2;
}
