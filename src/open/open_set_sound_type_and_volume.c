#include "psx/types.h"

extern void put_sound_type(s16 sound_type);
extern void calculate_change_in_volume(s32 volume, s16 duration);

void open_set_sound_type_and_volume(s32 sound_type, s32 duration) {
    s32 volume;

    if (sound_type == 0) {
        volume = 0;
    } else {
        put_sound_type((s16)sound_type);
        volume = 0x6400;
    }

    calculate_change_in_volume(volume, (s16)duration);
}
