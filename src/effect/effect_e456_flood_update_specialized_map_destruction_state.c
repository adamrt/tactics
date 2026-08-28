typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;

typedef struct EffectState {
    u8 padding[0x22];
    u8 phase;
} EffectState;

extern u8 g_effect_state_records[][0xf8];
extern void dispatch_map_data_command(s32 command, s32 arg1, s32 arg2, s32 arg3);
extern void set_specialized_map_state_destroyed(void);

s32 effect_e456_flood_update_specialized_map_destruction_state(s16 record_index, s32 byte_offset) {
    u8* record = g_effect_state_records[record_index];
    EffectState* state = (EffectState*)(record + byte_offset);

    switch (state->phase) {
    case 0:
        break;
    case 1:
        dispatch_map_data_command(0x9a, 1, 1, 1);
        state->phase = 2;
        break;
    case 2:
        set_specialized_map_state_destroyed();
        break;
    case 3:
        state->phase = 0;
        break;
    }
}
