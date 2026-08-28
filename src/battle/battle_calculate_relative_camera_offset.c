#include "psx/types.h"

/* Zero-instruction hint: keeps `input + 0xe` as its own value so GCC does not
 * re-associate it into `input - (offset - 0xe)`; the target adds first. */
#define KEEP(x) __asm__("" : "=r"(x) : "0"(x))

extern u16 g_battle_camera_yaw;

void battle_calculate_relative_camera_offset(const volatile u16* input,
    s16* output, s32 offset) {
    s32 result;
    s32 tmp;
    s32 yaw;

    output[1] = input[1] - 0xc;
    __asm__ volatile("" : : : "memory");
    yaw = g_battle_camera_yaw & 0xc00;

    switch (yaw) {
    case 0:
        tmp = input[0] + 0xe;
        KEEP(tmp);
        result = tmp - offset;
        goto store_x;
    case 0x400:
        tmp = input[0] + 0xe;
        KEEP(tmp);
        result = tmp - offset;
        output[0] = result;
        __asm__ volatile("" : : : "memory");
        tmp = input[2] + 0xe;
        KEEP(tmp);
        result = tmp - offset;
        goto store_z;
    case 0x800:
        tmp = input[0] - 0xe;
        KEEP(tmp);
        result = tmp + offset;
        output[0] = result;
        __asm__ volatile("" : : : "memory");
        tmp = input[2] + 0xe;
        KEEP(tmp);
        result = tmp - offset;
        goto store_z;
    case 0xc00:
        tmp = input[0] - 0xe;
        KEEP(tmp);
        result = tmp + offset;
        goto store_x;
    }
    return;

store_x:
    output[0] = result;
    tmp = input[2] - 0xe;
    KEEP(tmp);
    result = tmp + offset;
store_z:
    output[2] = result;
}
