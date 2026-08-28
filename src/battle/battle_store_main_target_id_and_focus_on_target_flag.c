#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_unit_decision_t* g_ai_acting_unit_decision_ptr;
extern void battle_transfer_unit_coordinates_to_ai(s32 unit_id);

/* Record the acting unit's main_entrypoint target and set "focus on target" (0x40),
 * clearing "stay near" (0x20); then copy the target's coordinates into the
 * AI block. */
void battle_store_main_target_id_and_focus_on_target_flag(s32 unit_id) {
    register battle_ai_unit_decision_t* decision __asm__("$5") = g_ai_acting_unit_decision_ptr;
    u8 flags = decision->flags;

    decision->main_target_id = unit_id;
    decision->flags = (flags | 0x40) & 0xDF;
    battle_transfer_unit_coordinates_to_ai(unit_id);
}
