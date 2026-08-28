#include "psx/types.h"

extern void func_80133FE8(void*);
extern void func_80134020(void);
extern void func_8014C8A0(s32, void*);
extern void func_8014CA38(s32, s32, s32, s32);

extern volatile s32 g_jobstts_selected_job_text_id;
extern u8 D_801E5508[];
extern u8 text_character_handling_thread[];

void jobstts_start_selected_job_text_thread(s32 thread_data) {
    if (g_jobstts_selected_job_text_id > 0) {
        func_80134020();
        func_80133FE8(D_801E5508);
        func_8014C8A0(1, text_character_handling_thread);
        func_8014CA38(1, thread_data + 0x38, g_jobstts_selected_job_text_id, 0);
        *(s32*)0x80166028 = 1;
    }
}
