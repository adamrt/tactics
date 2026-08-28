typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;

typedef struct EffectState {
    u8 padding[0x22];
    u8 phase;
} EffectState;

typedef struct EffectRecord {
    u8 bytes[0xf8];
} EffectRecord;

extern EffectRecord g_effect_state_records[];
extern void battle_map_unfreeze(void);

s32 effect_e450_dejeon_send_step_map_unfreeze_state(s16 record_index, s32 byte_offset) {
    EffectRecord* record;
    EffectState* state;

    record = &g_effect_state_records[record_index];
    state = (EffectState*)((u8*)record + byte_offset);

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
