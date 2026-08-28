#include "psx/types.h"

extern s32 g_attack_selected_roster_index;
extern s32 g_attack_pending_roster_index;
extern s32 D_801cd210;
extern s32 g_attack_roster_navigation_direction;
extern s32 g_attack_selected_unit_deployed;
extern s32 D_801cd230;
extern s32 D_801cd244;
extern u8 g_attack_roster_unit_deployable[20];

extern void attack_mark_other_squad_units_undeployable(void);
extern s32 attack_is_roster_unit_deployed(s32 roster_id);
extern void attack_copy_unit_data_to_status_billboard(s32 mode,
    s32 roster_index);
extern void switch_to_next_event_thread(void);
extern void stop_current_event_thread(void);

void attack_select_previous_deployable_roster_unit(void) {
    s32 pending;

    attack_mark_other_squad_units_undeployable();
    pending = g_attack_pending_roster_index;
    if (pending != -1) {
        g_attack_selected_roster_index = pending;
        g_attack_pending_roster_index = -1;
    } else {
        do {
            g_attack_selected_roster_index--;
            if (g_attack_selected_roster_index < 0) {
                g_attack_selected_roster_index = 19;
            }
        } while (g_attack_roster_unit_deployable[g_attack_selected_roster_index] == 0);
    }
    attack_copy_unit_data_to_status_billboard(
        1, g_attack_selected_roster_index);
    g_attack_roster_navigation_direction = 2;
    D_801cd210 = 0;
    D_801cd230 = 1;
    D_801cd244 = 1;
    g_attack_selected_unit_deployed = attack_is_roster_unit_deployed(g_attack_selected_roster_index);
    switch_to_next_event_thread();
    stop_current_event_thread();
}
