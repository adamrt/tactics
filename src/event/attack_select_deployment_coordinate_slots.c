#include "psx/types.h"

extern s32 g_attack_second_deployment_pass;
extern u8 g_deployed_unit_map_coordinates;

void* attack_select_deployment_coordinate_slots(void) {
    void* coordinate_slots;

    if (g_attack_second_deployment_pass != 0) {
        coordinate_slots = &g_deployed_unit_map_coordinates + 0x18;
    } else {
        g_attack_second_deployment_pass = 1;
        coordinate_slots = &g_deployed_unit_map_coordinates;
    }

    return coordinate_slots;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
