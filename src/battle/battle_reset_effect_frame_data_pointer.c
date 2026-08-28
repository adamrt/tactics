#include "psx/types.h"

extern u8* g_effect_frame_data_start;
extern u8* g_effect_frame_data;

void battle_reset_effect_frame_data_pointer(void) {
    g_effect_frame_data = g_effect_frame_data_start;
}
