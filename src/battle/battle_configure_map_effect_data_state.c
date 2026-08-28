#include "psx/types.h"

enum {
    MAP_EFFECT_DATA_END = 0x87,
    MAP_EFFECT_DATA_BEGIN = 0x88,
};

extern s32 D_80121d58;
extern s32 D_800fc558;

s32 battle_configure_map_effect_data_state(s32 command) {
    s32 result;

    switch (command) {
    case MAP_EFFECT_DATA_END:
        result = 4;
        D_80121d58 = 0;
        D_800fc558 = result;
        break;
    case MAP_EFFECT_DATA_BEGIN:
        result = -1;
        D_80121d58 = result;
        D_800fc558 = 0;
        break;
    default:
        result = -1;
        break;
    }
    return result;
}
