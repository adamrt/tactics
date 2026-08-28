#include "psx/types.h"

extern s32 g_require_panel_dim_a;
extern s32 g_require_panel_dim_b;
extern s32 g_require_panel_dim_c;
extern u8 g_require_status_animation[];

void require_broadcast_transition_value(s32 value) {
    g_require_panel_dim_a = value;
    g_require_panel_dim_b = value;
    g_require_panel_dim_c = value;
    g_require_status_animation[0] = value;
    g_require_status_animation[1] = value;
}
