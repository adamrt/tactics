#include "psx/types.h"

extern s32 battle_get_script_variable(s32 variable_id);
extern s32 rand(void);
extern void main_open_entd(void);

extern volatile s32 g_battle_entd_selection_mode;
extern volatile s32 g_current_event_id;
extern s32 g_battle_map_id;

void battle_select_and_open_battle_entd(void) {
    volatile s32* current_event_id;
    s32 event_id;
    s32 selection_mode;

    event_id = battle_get_script_variable(0x32);
    selection_mode = g_battle_entd_selection_mode;
    current_event_id = &g_current_event_id;
    *current_event_id = event_id;

    if (selection_mode == 1) {
        *current_event_id = 250;
    } else if (selection_mode == 2) {
        *current_event_id = (rand() * 5) / 0x8000 + 75;
    } else if (selection_mode == 3) {
        *current_event_id = (rand() * 59) / 0x8000 + 1;
    } else if ((selection_mode == 4) && (g_battle_map_id != 0)) {
        *current_event_id = g_battle_map_id;
    }

    main_open_entd();
}
