#include "psx/types.h"

extern void battle_load_next_event(void);
extern void func_80143BD8(void);

void battle_func_80143b80(void) {
    battle_load_next_event();
    func_80143BD8();
}
