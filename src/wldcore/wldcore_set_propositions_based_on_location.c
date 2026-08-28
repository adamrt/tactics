#include "psx/types.h"

/* Proposition record as copied out by func_80069934 ("Store Proposition
 * Data", wiki page 00002315).  Only the fields this check reads are named:
 * 0x20 is compared against the current map location, 0x22 selects which of
 * the remaining conditions apply, 0x2c doubles as the required month (bit 1)
 * and the proposition status index (bit 2, script variable 0x360 + n). */
typedef struct {
    u8 unk_00[0x20];
    u16 location;
    u16 condition_flags;
    u8 unk_24[6];
    u16 required_script_var_6f;
    u16 condition_value;
    u16 unk_2e;
} PropositionEntry;

enum {
    PROPOSITION_CONDITION_SCRIPT_VAR_6F = 1,
    PROPOSITION_CONDITION_MONTH = 2,
    PROPOSITION_CONDITION_STATUS = 4,
};

extern void func_80069934(PropositionEntry* out, s32 index);
extern void func_80069BB0(s32* month, s32* day);
extern s32 world_get_script_variable(s32 variable_id);

s32 wldcore_set_propositions_based_on_location(s32 index, s32 location) {
    PropositionEntry entry;
    s32 month;
    s32 day;

    func_80069934(&entry, index);
    if (entry.location != 0) {
        if (location != entry.location) {
            return 0;
        }
    }
    if (entry.condition_flags & PROPOSITION_CONDITION_SCRIPT_VAR_6F) {
        if (world_get_script_variable(0x6F) < entry.required_script_var_6f) {
            return 0;
        }
    }
    if (entry.condition_flags & PROPOSITION_CONDITION_MONTH) {
        month = world_get_script_variable(0x2E);
        day = world_get_script_variable(0x2F);
        func_80069BB0(&month, &day);
        if (month != entry.condition_value) {
            return 0;
        }
    }
    if (entry.condition_flags & PROPOSITION_CONDITION_STATUS) {
        if ((world_get_script_variable(entry.condition_value + 0x360) & 4) == 0) {
            return 0;
        }
    }
    return 1;
}
