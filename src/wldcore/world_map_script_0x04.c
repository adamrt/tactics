#include "fft/data.h"

extern s32 g_world_script_flags;
extern u16* g_world_script_data_ptr;
extern u16 g_world_script_ip;
extern party_data_t* wldcore_get_party_data_pointer(s32 index);

/* Flag 2 if no roster unit has the operand's sprite set. */
void world_map_script_0x04(void) {
    s32 i;
    s32 sprite_set;
    u16* ipp;
    u16 ip;
    party_data_t* unit;
    s32* flags;

    ipp = &g_world_script_ip;
    ip = *ipp;
    sprite_set = g_world_script_data_ptr[ip];
    *ipp = ip + 1;
    for (i = 0; i < 20; i++) {
        unit = wldcore_get_party_data_pointer(i);
        if (unit->party_id != PARTY_ID_NONE) {
            if (unit->sprite_set == sprite_set) {
                break;
            }
        }
    }
    if (i == 20) {
        flags = &g_world_script_flags;
        *flags |= 0x2;
    }
}
