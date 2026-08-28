#include "psx/types.h"

extern void func_801A5110(void);
extern void battle_effect_related(void);
extern void func_801A5B48(void);
extern void func_801A9F44(void);

void battle_func_801aa8e8(void) {
    func_801A5110();
    battle_effect_related();
    func_801A5B48();
    func_801A9F44();
}
