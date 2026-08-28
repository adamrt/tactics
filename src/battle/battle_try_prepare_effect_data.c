#include "psx/types.h"

extern s32 prepare_effect_data(void);

s32 battle_try_prepare_effect_data(void) {
    return prepare_effect_data() != 0;
}
