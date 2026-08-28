#include "psx/types.h"

typedef struct EquipThreadTask {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u16 unk_6;
} EquipThreadTask;

typedef struct EquipEventThread {
    /* 0x00 */ u8 unk_0[0x1C];
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 unk_1E[0xE];
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u8 unk_2E[2];
    /* 0x30 */ EquipThreadTask* task;
} EquipEventThread;

extern s32 g_current_event_thread_id;
extern s32 g_event_threads;
extern s32* g_equip_controller_input;

extern s32* battle_get_controller_input_pointer(s32 port);
extern void battle_handle_menu_action(EquipEventThread* thread, s32 arg1);
extern void initialize_event_thread(s32 thread_id, void* entry);
extern void store_thread_parameters_5(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void wait_for_event_thread(s32 thread_id);
extern void stop_current_event_thread(void);
extern void text_character_handling_thread(void);

void equip_open_submenu_thread_from_current(void) {
    EquipEventThread* thread;
    EquipThreadTask* task;
    s32* input;
    s32 unk_1c;
    s32 unk_2c;
    u16 child_id;
    u16 task_arg;

    thread = *(EquipEventThread**)((g_current_event_thread_id << 10) + g_event_threads);
    thread->task->func();

    input = battle_get_controller_input_pointer(0);
    unk_1c = thread->unk_1C;
    task = thread->task;
    unk_2c = thread->unk_2C;
    g_equip_controller_input = input;
    child_id = task->unk_6;
    task_arg = task->unk_4;
    *input = 0x20;
    battle_handle_menu_action(thread, 0);

    initialize_event_thread(child_id, text_character_handling_thread);
    store_thread_parameters_5(child_id, unk_2c, unk_1c, task_arg, task_arg);
    wait_for_event_thread(g_current_event_thread_id - 1);
    wait_for_event_thread(child_id);
    stop_current_event_thread();
}
