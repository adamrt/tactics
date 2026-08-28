#include "psx/types.h"

extern s32* g_world_event_words;

extern void world_set_script_variable(s32 variable_id, s32 value);
extern void world_run_event_instruction(s32 opcode, s32 parameter_1, s32 parameter_2, s32 parameter_3);

s32 world_get_script_variable(s32 variable_id) {
    s32 saved = *g_world_event_words;

    if (variable_id == 0x22) {
        s32 tod;
        s32 wth;
        s32 tod_bits;
        s32 wth_bits;

        tod = world_get_script_variable(0x24) & 1;
        /* Both fences below only order instructions: without them GCC hoists
         * the next call's `li a0` above the andi / the or into the delay slot. */
        __asm__ volatile("" : : "r"(tod));
        wth = world_get_script_variable(0x23) & 7;
        tod_bits = tod << 15;
        wth_bits = wth << 12;
        __asm__ volatile("" : : "r"(wth_bits));
        world_set_script_variable(0x22, tod_bits | wth_bits);
    }
    world_run_event_instruction(0xbe, 0, 0, 0);
    world_run_event_instruction(0xb1, 0, variable_id, 0);
    {
        s32 val = *g_world_event_words;

        *g_world_event_words = saved;
        return val;
    }
}
