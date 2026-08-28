#include "psx/types.h"

typedef struct TempEffectData {
    u8 _pad00[0x26];
    s16 field_26;
    s16 field_28;
    s16 values_2a[13];
    s16 values_44[13];
    s16 values_5e[13];
} TempEffectData;

void battle_clear_temp_effect_data(TempEffectData* data, s16 value) {
    s32 index;

    index = 0;
    do {
        data->values_5e[index] = 0;
        data->values_44[index] = 0;
        data->values_2a[index] = 0;
        index++;
    } while (index < 13);
    data->field_28 = 0;
    data->field_26 = value;
}
