#include "psx/types.h"

typedef struct TempEffectData2 {
    u8 _pad00[0x28];
    s16 field_28;
    s16 field_2a;
    s16 field_2c;
    s16 values_2e[26];
    s16 values_62[26];
    s16 values_96[26];
} TempEffectData2;

void battle_clear_temp_effect_data_2(TempEffectData2* data) {
    s32 index;

    index = 0;
    do {
        data->values_96[index] = 0;
        data->values_62[index] = 0;
        data->values_2e[index] = 0;
        index++;
    } while (index < 26);
    data->field_2a = 0;
    data->field_28 = 0;
    data->field_2c = 0;
}
