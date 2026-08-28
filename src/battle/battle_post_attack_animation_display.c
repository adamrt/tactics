#include "psx/types.h"

extern void set_target_anim_from_attack_type(void);
extern void battle_jump_to_post_action_display(u8 arg);

void battle_post_attack_animation_display(s32 flag, u8* ctx) {
    if (flag != 0 && ctx != 0) {
        set_target_anim_from_attack_type();
        battle_jump_to_post_action_display(ctx[4]);
    }
}
