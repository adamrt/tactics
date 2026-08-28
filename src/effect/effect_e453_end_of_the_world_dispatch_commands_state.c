typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;

typedef struct EffectState {
    u8 padding[0x22];
    u8 phase;
} EffectState;

extern u8 g_effect_state_records[][0xf8];
extern void dispatch_map_data_command(s32 command, s32 index, s32 group,
    s32 enabled);

s32 effect_e453_end_of_the_world_dispatch_commands_state(s16 record_index,
    s32 byte_offset) {
    u8* record = g_effect_state_records[record_index];
    EffectState* state = (EffectState*)(record + byte_offset);

    switch (state->phase) {
    case 0:
        break;
    case 1:
        dispatch_map_data_command(0x98, 1, 1, 1);
        dispatch_map_data_command(0x80, 1, 3, 1);
        dispatch_map_data_command(0x80, 2, 3, 1);
        dispatch_map_data_command(0x80, 3, 3, 1);
        dispatch_map_data_command(0x80, 4, 3, 1);
        dispatch_map_data_command(0x80, 5, 3, 1);
        dispatch_map_data_command(0x80, 6, 3, 1);
        dispatch_map_data_command(0x80, 7, 3, 1);
        dispatch_map_data_command(0x80, 8, 3, 1);
        state->phase = 2;
        break;
    case 2:
        break;
    case 3:
        state->phase = 0;
        break;
    }
}
