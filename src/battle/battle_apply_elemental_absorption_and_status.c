#include "psx/types.h"

extern s32 conditional_status_proc_roll(void);
extern void apply_elemental_absorption(void);
extern void apply_status_to_action(void);

s32 battle_apply_elemental_absorption_and_status(void) {
    s32 result;

    apply_elemental_absorption();
    result = conditional_status_proc_roll();
    if (result == 0) {
        apply_status_to_action();
        return 0;
    }
    return result;
}
