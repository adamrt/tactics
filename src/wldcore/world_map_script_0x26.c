#include "fft/data.h"

extern s32 wldcore_get_ramza_s_roster_index(void);
extern party_data_t* wldcore_get_party_data_pointer(s32);
extern u16 g_world_script_ip;
extern u16* g_world_script_data_ptr;
extern s32 g_world_script_flags;

/* Flag 2 if Ramza's brave is above the operand. */
void world_map_script_0x26(void) {
    party_data_t* party;
    u16* ipp;
    u16 ip;
    s32 val;

    party = wldcore_get_party_data_pointer(wldcore_get_ramza_s_roster_index());
    ipp = &g_world_script_ip;
    ip = *ipp;
    val = g_world_script_data_ptr[ip];
    *ipp = ip + 1;
    if (val < (s32)party->bravery) {
        g_world_script_flags |= 2;
    }
}
