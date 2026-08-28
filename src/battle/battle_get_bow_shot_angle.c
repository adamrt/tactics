#include "psx/types.h"

extern s16 g_arctan_angle_mod;

/* Wrap the current bow-shot yaw into (-0x800, 0x800] then bucket it into
   one of three arc quadrants: 0 = behind, 1 = side, 2 = ahead. */
s32 battle_get_bow_shot_angle(void) {
    s16 angle = g_arctan_angle_mod;
    if (angle >= 0x801) {
        g_arctan_angle_mod = angle - 0x1000;
    }
    {
        s16 angle_after_hi = g_arctan_angle_mod;
        if (angle_after_hi < -0x800) {
            g_arctan_angle_mod = angle_after_hi + 0x1000;
        }
    }
    {
        s16 wrapped = g_arctan_angle_mod;
        if (wrapped < 0x2AB) {
            return wrapped >= -0x2AA;
        }
        return 2;
    }
}
