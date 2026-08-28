#include "psx/types.h"

typedef struct {
    s8 a;
    s8 b;
    s8 c[3];
} TargetingPanelEntry;

extern TargetingPanelEntry targeting_panel_data[0x200];

void battle_clear_targeting_panel_data(void) {
    s32 i = 0;
    TargetingPanelEntry* p = targeting_panel_data;
    for (; i < 512; i++) {
        p->a = 0;
        p->b = 0;
        p++;
    }
}
