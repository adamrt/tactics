#include "psx/types.h"

extern s16 world_load_halfword(const void* source);
extern s32 world_get_misc_id(s16 unit_id);
extern void battle_unset_misc_data_move_flag_bit_1(s16 misc_id);
extern void battle_flip_misc_data_move_flag_bit_1(s16 misc_id);
extern void world_set_unit_facing(s32 misc_id, u8 rotation);
extern void world_set_unit_animation(s32 misc_id, s16 value);
extern u8 g_world_unit_animation_states[];

void world_unit_animation_rotate(const u8* parameters) {
    const u8* data = parameters;
    u8 rotation;
    s16 value;
    s16 call_misc_id;
    s16 misc_id;
    s32 index;
    u8* state;

    misc_id = world_load_halfword(data);
    rotation = data[2];
    value = world_load_halfword(data + 3);
    call_misc_id = world_get_misc_id(misc_id);
    misc_id = call_misc_id;
    if (data[4] == 0) {
        battle_unset_misc_data_move_flag_bit_1(call_misc_id);
    } else {
        battle_flip_misc_data_move_flag_bit_1(call_misc_id);
    }
    index = misc_id;
    state = &g_world_unit_animation_states[index * 7];
    state[0] = rotation;
    state[6] = 0;
    state[4] = 0;
    world_set_unit_facing(index, rotation);
    world_set_unit_animation(index, value);
}
