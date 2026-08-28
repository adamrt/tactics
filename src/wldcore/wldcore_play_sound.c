#include "psx/types.h"

extern void main_play_sound(s32 sound_id);

void wldcore_play_sound(s32 sound_id) {
    main_play_sound(sound_id);
}
