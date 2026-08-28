#include "psx/types.h"

typedef struct {
    u8 _pad[0x1e];
    s16 field_1e;
} MenuCtx;

extern s32 func_80137B98(void);
extern void battle_set_sound_effect_to_cursor_move(void);
extern u32 g_battle_event_input;

void battle_update_menu_selection_from_input(MenuCtx* ctx, s32* sel) {
    s32 a;
    s32 max;
    s32 cur;

    if (func_80137B98() != 0) {
        if (g_battle_event_input & 0x1000) {
            a = *sel;
            if (a == 0) {
                a = ctx->field_1e;
            } else {
                a = a - 1;
            }
            *sel = a;
            battle_set_sound_effect_to_cursor_move();
        }
        if (g_battle_event_input & 0x4000) {
            max = ctx->field_1e;
            cur = *sel;
            if (cur == max) {
                *sel = 0;
            } else {
                *sel = cur + 1;
            }
            battle_set_sound_effect_to_cursor_move();
        }
    }
}
