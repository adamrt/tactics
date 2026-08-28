#include "fft/data.h"

void world_store_thread_function_parameters_4(s32 thread_id, s32 first, s32 second, s32 third, s32 fourth) {
    g_world_threads[thread_id].function_parameter_1 = first;
    g_world_threads[thread_id].function_parameter_2 = second;
    g_world_threads[thread_id].function_parameter_3 = third;
    g_world_threads[thread_id].unk_0c = fourth;
}
