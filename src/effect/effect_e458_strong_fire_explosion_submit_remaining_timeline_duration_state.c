typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct EffectState {
    u8 padding[0x22];
    u8 phase;
} EffectState;

typedef struct EffectRecord {
    u8 padding[0x28];
    s16 effect_timer;
} EffectRecord;

typedef struct EffectTimelineHeader {
    u16 unknown_0;
    u16 effect_duration;
} EffectTimelineHeader;

extern u8 g_effect_state_records[][0xf8];
extern EffectTimelineHeader* g_effect_timeline_channel_base;
extern void set_map_command_0x96_duration(s32 command, s32 remaining_duration);

s32 effect_e458_strong_fire_explosion_submit_remaining_timeline_duration_state(s16 record_index, s32 byte_offset) {
    s32 record_offset;
    u8* table;
    u8* record;
    EffectState* state;
    record_offset = record_index * 0xf8;
    table = (u8*)g_effect_state_records;
    record = table + record_offset;
    state = (EffectState*)(record + byte_offset);

    switch (state->phase) {
    case 0:
        break;
    case 1:
        set_map_command_0x96_duration(0x96, g_effect_timeline_channel_base->effect_duration - ((EffectRecord*)record)->effect_timer);
        state->phase = 2;
        break;
    case 2:
        break;
    case 3:
        state->phase = 0;
        break;
    }
}
