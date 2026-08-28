#include "psx/types.h"

typedef struct {
    u8 pad0[0x58];
    u8 x58;
    u8 x59;
    u8 x5A;
    u8 x5B;
    u8 x5C;
} TargetData;

extern TargetData* g_current_target;
extern u8 g_current_ability_base_hit;
extern u8 D_801938DE[2];

extern void main_clear_byte_data(u8*, s32);

void battle_evasion_changes_due_to_statuses(void) {
    TargetData* t;
    u8 flag;
    u8* p;

    t = g_current_target;
    flag = (t->x5C & 0x14) != 0;
    if (t->x5B & 2) {
        flag = 1;
    }
    if (t->x59 & 0x10) {
        flag = 1;
    }
    if (t->x58 & 9) {
        flag = 1;
    }
    if (flag) {
        main_clear_byte_data(D_801938DE, 4);
    }
    if (g_current_target->x58 & 2) {
        p = &g_current_ability_base_hit;
        *p >>= 1;
    }
}
