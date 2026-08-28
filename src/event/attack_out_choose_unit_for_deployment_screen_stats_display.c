#include "psx/types.h"

extern s32 g_attack_selected_roster_index;
extern s32 D_801cd210;
extern u8 g_attack_roster_unit_deployable[20];

extern void attack_mark_other_squad_units_undeployable(void);
extern void attack_copy_unit_data_to_status_billboard(s32 mode,
    s32 roster_index);

void attack_out_choose_unit_for_deployment_screen_stats_display(void) {
    attack_mark_other_squad_units_undeployable();
    while (1) {
        if (g_attack_selected_roster_index >= 20) {
            g_attack_selected_roster_index = 0;
        }
        if (g_attack_roster_unit_deployable[g_attack_selected_roster_index] != 0) {
            break;
        }
        g_attack_selected_roster_index++;
    }
    D_801cd210 = 0;
    attack_copy_unit_data_to_status_billboard(1, g_attack_selected_roster_index);
}
