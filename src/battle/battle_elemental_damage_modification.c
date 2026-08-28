#include "psx/types.h"

extern u8 D_80193904;
extern void battle_elemental_damage_modification_2(u8 arg);

void battle_elemental_damage_modification(void) {
    battle_elemental_damage_modification_2(D_80193904);
}
