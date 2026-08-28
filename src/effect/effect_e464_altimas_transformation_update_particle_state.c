/* E464: Altima's Transformation; target/wiki range ends before trailing data. */
typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;

#define NULL ((void*)0)

typedef struct EffectState {
    u8 padding[0x22];
    u8 phase;
} EffectState;

typedef struct EffectRecord {
    u8 padding_00[2];
    s16 origin_x;
    u8 padding_04[0x1c];
    s16 origin_y;
    u8 padding_22[0xc2];
    void* work_slots[1];
} EffectRecord;

typedef struct EffectParticleSystemEntry {
    u8 padding_00[0x4c];
    s16 job;
    u8 padding_4e[0x5a];
    s16 start_frame;
    s16 end_frame;
} EffectParticleSystemEntry;

typedef struct EffectWorkVertex {
    s32 x;
    s32 y;
    s32 z;
} EffectWorkVertex;

typedef struct EffectTransform {
    u8 padding_00[0x0c];
    s32 x;
    s32 y;
    s32 z;
    u8 padding_18[0x40];
} EffectTransform;

extern u8 g_effect_state_records[][0xf8];
extern void* g_current_effect_work;
extern u8* g_effect_particle_system_data;
extern u8 g_altima_transformation_job_work_offset_scale_16;
extern u8 g_altima_transformation_job_work_offset_scale_64;

extern s32 effect_work_free(void* work);
extern void* effect_work_allocate(s32 bytes, s32 record_index);
extern s32 dispatch_map_data_command(s32 command, s32 index, s32 group,
    s32 enabled);
extern s32 render_effect_emitter_particles(s16 origin_x, s32 relative_y,
    s32 particle_index,
    EffectTransform* transform);

s32 effect_e464_altimas_transformation_update_particle_state(
    s32 record_index, s32 byte_offset, s32 unused, s32 frame) {
    s16 effect_slot;
    s32 record_offset;
    register u8* state_table __asm__("$3");
    register EffectRecord* record __asm__("$17");
    EffectState* state;
    u8* work;
    EffectTransform transform;
    s32 particle_index;
    s32 particle_offset;
    s32 job_index;
    s32 work_offset;
    EffectParticleSystemEntry* particle;
    EffectWorkVertex* vertex;
    register EffectRecord* destroy_record __asm__("$16");
    void* new_work;

    (void)unused;
    record_index <<= 16;
    effect_slot = record_index >> 16;
    record_offset = effect_slot * 0xf8;
    state_table = (u8*)g_effect_state_records;
    record = (EffectRecord*)(state_table + record_offset);
    state = (EffectState*)((u8*)record + byte_offset);

    switch (state->phase) {
    case 0:
        break;
    case 1:
        record_offset = byte_offset * 4;
        record = (EffectRecord*)(record_offset + (s32)record);
        if (record->work_slots[0] != NULL) {
            effect_work_free(record->work_slots[0]);
        }
        new_work = effect_work_allocate(0x200, effect_slot);
        record->work_slots[0] = new_work;
        g_current_effect_work = new_work;
        dispatch_map_data_command(0x80, 1, 1, 1);
        dispatch_map_data_command(0x80, 2, 1, 1);
        dispatch_map_data_command(0x80, 3, 1, 1);
        dispatch_map_data_command(0x80, 4, 1, 1);
        dispatch_map_data_command(0x80, 5, 1, 1);
        dispatch_map_data_command(0x80, 6, 1, 1);
        state->phase = 2;
        break;
    case 2:
        work = *(u8**)((u8*)record + byte_offset * 4 + 0xe4);
        particle_index = 0;
        particle_offset = 0x14;
        do {
            particle = (EffectParticleSystemEntry*)(g_effect_particle_system_data + particle_offset);
            job_index = particle->job - 1;
            if ((u32)job_index < 12 && frame >= particle->start_frame && frame < particle->end_frame) {
                work_offset = (*(&g_altima_transformation_job_work_offset_scale_16 + job_index * 2)
                                  << 4)
                    + (*(&g_altima_transformation_job_work_offset_scale_64 + job_index * 2)
                        << 6);
                vertex = (EffectWorkVertex*)(work + work_offset);
                transform.x = vertex->x << 12;
                transform.y = vertex->y << 12;
                transform.z = vertex->z << 12;
                render_effect_emitter_particles(record->origin_x,
                    record->origin_y - particle->start_frame,
                    particle_index, &transform);
            }
            particle_index++;
            particle_offset += 0xc4;
        } while (particle_index < 16);
        break;
    case 3:
        record_offset = byte_offset * 4;
        destroy_record = (EffectRecord*)(record_offset + (s32)record);
        if (destroy_record->work_slots[0] != NULL) {
            effect_work_free(destroy_record->work_slots[0]);
            destroy_record->work_slots[0] = NULL;
            g_current_effect_work = NULL;
        }
        state->phase = 0;
        break;
    }
}
