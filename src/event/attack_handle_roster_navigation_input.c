#include "psx/types.h"

extern s32 g_sound_effect_id_to_play;
extern s8 D_801cf5f0;
extern s8 D_801cf5f1;

extern s32* battle_get_controller_input_pointer(s32 controller_index);
extern void initialize_event_thread(s32 thread_id, void (*entrypoint)(void));
extern s32 is_event_thread_running(s32 thread_id);
extern void attack_select_next_deployable_roster_unit(void);
extern void attack_select_previous_deployable_roster_unit(void);

void attack_handle_roster_navigation_input(void) {
    s32* flags;

    flags = battle_get_controller_input_pointer(0);
    if ((*flags & 4) && (is_event_thread_running(4) == 0)) {
        D_801cf5f0 = 7;
        g_sound_effect_id_to_play = 6;
        initialize_event_thread(4,
            attack_select_previous_deployable_roster_unit);
    }
    if ((*flags & 8) && (is_event_thread_running(4) == 0)) {
        D_801cf5f1 = 7;
        g_sound_effect_id_to_play = 6;
        initialize_event_thread(4, attack_select_next_deployable_roster_unit);
    }
}
