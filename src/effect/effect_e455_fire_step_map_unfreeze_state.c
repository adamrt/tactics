typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;

typedef struct EffectState {
    u8 padding[0x22];
    u8 phase;
} EffectState;

extern u8 g_effect_state_records[][0xf8];
extern void battle_map_unfreeze(void);

s32 effect_e455_fire_step_map_unfreeze_state(s16 record_index, s32 byte_offset) {
    u8* record = g_effect_state_records[record_index];
    EffectState* state = (EffectState*)(record + byte_offset);

    switch (state->phase) {
    case 0:
        break;
    case 1:
        battle_map_unfreeze();
        state->phase = 2;
        break;
    case 2:
        break;
    case 3:
        state->phase = 0;
        break;
    }
}
