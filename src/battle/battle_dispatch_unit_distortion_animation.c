#include "psx/types.h"

typedef void (*BattleDistortionAnimationHandler)(u8* unit);

extern BattleDistortionAnimationHandler g_battle_distortion_animation_handlers[];
extern void main_animation_exception_handler(s32 exception_id);

void battle_dispatch_unit_distortion_animation(u8* unit) {
    u32 distortion_id = unit[0x87];

    if (distortion_id != 0) {
        if (distortion_id < 0x12) {
            g_battle_distortion_animation_handlers[distortion_id](unit);
        } else {
            main_animation_exception_handler(0x17);
        }
    }
}
