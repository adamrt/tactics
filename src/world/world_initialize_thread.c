#include "fft/data.h"

void* world_return_global_pointer(void);

void world_initialize_thread(s32 thread_id, void (*function)(void)) {
    void* global_pointer = world_return_global_pointer();
    world_thread_t* thread = &g_world_threads[thread_id];

    thread->global_pointer = global_pointer;
    thread->stack_pointer = (u32*)((u8*)thread + 0x3f0);
    thread->frame_pointer = (u32*)((u8*)thread + 0x3f0);
    thread->code_pointer = function;
    thread->is_running = 1;
    thread->task_id = 0;
    thread->unk_0c = 0;
    thread->unk_50[0] = 0;
    thread->unk_50[1] = 0;
    thread->unk_50[2] = 0;
    thread->unk_50[3] = 0;
    thread->unk_50[4] = 0;
    thread->unk_50[5] = 0;
    thread->unk_50[6] = 0;
}
