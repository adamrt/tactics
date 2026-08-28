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
extern u8 g_banish_work_offset_scale_16;
extern u8 g_banish_work_offset_scale_64;

extern s32 effect_work_free(void* work);
extern void* effect_work_allocate(s32 bytes, s32 record_index);
extern s32 dispatch_map_data_command(s32 command, s32 index, s32 group,
    s32 enabled);
extern s32 render_effect_emitter_particles(s16 origin_x, s32 relative_y,
    s32 particle_index,
    EffectTransform* transform);

s32 effect_e454_banish_update_particle_state(
    s32 record_index, s32 byte_offset, s32 unused, s32 frame) {
    s16 effect_slot;
    s32 record_offset;
    /* Pins and the two addiu asms hold a register-only allocation; the
     * switch/for rewrite used for the sibling handlers differs only in
     * $v0/$a0 temp choice here. */
    register u8* state_table __asm__("$3");
    EffectRecord* record;
    EffectState* state;
    u8* work;
    s32 particle_index;
    register s32 particle_offset __asm__("$22");
    s32 table_byte_offset;
    EffectParticleSystemEntry* particle;
    EffectRecord* destroy_record;
    EffectTransform transform;
    s32 job;
    s32 job_index;
    s32 work_offset;
    register s32 call_particle_index __asm__("$6");
    EffectTransform* transform_arg;
    EffectWorkVertex* vertex;
    void* new_work;
    s32 phase;
    s32 coordinate;

    (void)unused;
    record_index <<= 16;
    effect_slot = record_index >> 16;
    record_offset = effect_slot * 0xf8;
    state_table = (u8*)g_effect_state_records;
    record = (EffectRecord*)(state_table + record_offset);
    state = (EffectState*)((u8*)record + byte_offset);
    phase = state->phase;

    if (phase == 1) {
        goto initialize;
    }
    if (phase < 2) {
        goto done;
    }
    if (phase == 2) {
        goto update;
    }
    if (phase == 3) {
        goto destroy;
    }
    goto done;

initialize:
    record_offset = byte_offset * 4;
    particle = (EffectParticleSystemEntry*)(record_offset + (s32)record);
    if (*(void**)((u8*)particle + 0xe4) != NULL) {
        effect_work_free(*(void**)((u8*)particle + 0xe4));
    }
    new_work = effect_work_allocate(0x200, effect_slot);
    *(void**)((u8*)particle + 0xe4) = new_work;
    g_current_effect_work = new_work;
    dispatch_map_data_command(0x80, 1, 1, 1);
    dispatch_map_data_command(0x80, 2, 1, 1);
    dispatch_map_data_command(0x80, 3, 1, 1);
    dispatch_map_data_command(0x80, 4, 1, 1);
    dispatch_map_data_command(0x80, 5, 1, 1);
    dispatch_map_data_command(0x80, 6, 1, 1);
    state->phase = 2;
    goto done;

update:
    work = *(u8**)((u8*)record + byte_offset * 4 + 0xe4);
    particle_index = 0;
    particle_offset = 0x14;

particle_loop:
    record_offset = (s32)g_effect_particle_system_data;
    particle = (EffectParticleSystemEntry*)(particle_offset + record_offset);
    job = particle->job;
    job_index = job - 1;
    if ((u32)job_index < 12) {
        if (frame < particle->start_frame || frame >= particle->end_frame) {
            goto advance;
        }
        record_offset = job_index * 2;
        work_offset = *(&g_banish_work_offset_scale_16 + record_offset);
        record_offset = *(&g_banish_work_offset_scale_64 + record_offset);
        work_offset <<= 4;
        record_offset <<= 6;
        work_offset += record_offset;
        vertex = (EffectWorkVertex*)(work + work_offset);
        transform.x = vertex->x << 12;
        transform.y = vertex->y << 12;
        transform.z = vertex->z << 12;
        render_effect_emitter_particles(record->origin_x,
            record->origin_y - particle->start_frame,
            particle_index, &transform);
        goto advance_after_jump;
    }
    if (job == 13) {
        if (frame < particle->start_frame || frame >= particle->end_frame) {
            goto advance;
        }
        table_byte_offset = 0;
    emit_job_13:
        work_offset = *(&g_banish_work_offset_scale_16 + table_byte_offset);
        record_offset = *(&g_banish_work_offset_scale_64 + table_byte_offset);
        work_offset <<= 4;
        record_offset <<= 6;
        work_offset += record_offset;
        vertex = (EffectWorkVertex*)(work + work_offset);
        call_particle_index = particle_index;
        transform.x = vertex->x << 12;
        coordinate = vertex->y;
        __asm__ volatile("addiu %0,$29,0x10" : "=r"(transform_arg));
        transform.y = coordinate << 12;
        coordinate = vertex->z;
        __asm__ volatile("addiu %0,%0,2"
            : "=r"(table_byte_offset)
            : "0"(table_byte_offset));
        transform.z = coordinate << 12;
        render_effect_emitter_particles(record->origin_x,
            record->origin_y - particle->start_frame,
            call_particle_index, transform_arg);
        if (table_byte_offset < 8) {
            goto emit_job_13;
        }
        goto advance_after_jump;
    }
    if (job != 14) {
        goto advance;
    }
    if (frame < particle->start_frame || frame >= particle->end_frame) {
        goto advance;
    }
    table_byte_offset = 8;
emit_job_14:
    work_offset = *(&g_banish_work_offset_scale_16 + table_byte_offset);
    record_offset = *(&g_banish_work_offset_scale_64 + table_byte_offset);
    work_offset <<= 4;
    record_offset <<= 6;
    work_offset += record_offset;
    vertex = (EffectWorkVertex*)(work + work_offset);
    call_particle_index = particle_index;
    transform.x = vertex->x << 12;
    coordinate = vertex->y;
    __asm__ volatile("addiu %0,$29,0x10" : "=r"(transform_arg));
    transform.y = coordinate << 12;
    coordinate = vertex->z;
    __asm__ volatile("addiu %0,%0,2"
        : "=r"(table_byte_offset)
        : "0"(table_byte_offset));
    transform.z = coordinate << 12;
    render_effect_emitter_particles(record->origin_x,
        record->origin_y - particle->start_frame,
        call_particle_index, transform_arg);
    if (table_byte_offset < 24) {
        goto emit_job_14;
    }
    goto advance;

advance:
    particle_index++;
    goto test_loop;

advance_after_jump:
    particle_index++;

test_loop:
    particle_offset += 0xc4;
    if (particle_index < 16) {
        goto particle_loop;
    }
    goto done;

destroy:
    record_offset = byte_offset * 4;
    destroy_record = (EffectRecord*)(record_offset + (s32)record);
    if (destroy_record->work_slots[0] != NULL) {
        effect_work_free(destroy_record->work_slots[0]);
        destroy_record->work_slots[0] = NULL;
        g_current_effect_work = NULL;
    }
    state->phase = 0;

done:
    return;
}
