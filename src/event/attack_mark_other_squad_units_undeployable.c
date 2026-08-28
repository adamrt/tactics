#include "psx/types.h"

extern u8 g_attack_unit_fieldable[20];
extern u8 g_attack_roster_unit_deployable[20];
extern u8 g_attack_deployed_units_by_squad[4][25];
extern s32 g_attack_current_squad;

extern void world_copy_bytes(void* destination, const void* source, s32 size);

void attack_mark_other_squad_units_undeployable(void) {
    s32 squad_id;
    s32 empty;
    s32 unit_id;
    u8* squad;
    u8* entry;

    world_copy_bytes(g_attack_roster_unit_deployable, g_attack_unit_fieldable, 20);
    squad_id = 0;
    empty = 0xff;
    squad = g_attack_deployed_units_by_squad[0];
    do {
        if (squad_id != g_attack_current_squad) {
            entry = squad;
            do {
                unit_id = *entry++;
                if (unit_id != empty) {
                    g_attack_roster_unit_deployable[unit_id] = 0;
                }
            } while ((s32)entry < (s32)(squad + 25));
        }
        squad_id++;
        squad += 25;
    } while (squad_id < 4);
}
