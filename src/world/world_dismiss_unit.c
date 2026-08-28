#include "fft/data.h"

extern s32 world_dismiss_able_check(s16 formation_idx);
extern void func_80124428(s16 formation_idx, s16 i, s32 zero);
extern void main_remove_unit_from_party(s16 roster_slot);

void world_dismiss_unit(s16 formation_idx) {
    s32 i;

    if (world_dismiss_able_check(formation_idx) != 0) {
        i = 0;
        do {
            func_80124428(formation_idx, i, 0);
            i += 1;
        } while (i < 5);
        main_remove_unit_from_party(g_world_formation_unit_pointers[formation_idx]->roster_slot);
    }
}
