#include "psx/types.h"

typedef struct {
    u8 pad[0x28];
    void (*entry)(void);
} EquipMenuDescriptor;

extern s32 g_equip_thread_state;
extern EquipMenuDescriptor* g_menu_descriptor;

extern s32 is_event_thread_running(s32 thread_id);
extern void initialize_event_thread(s32 thread_id, void (*entry)(void));
extern void battle_store_thread_function_parameters(s32 thread_id, s32 parameter_0,
    s32 parameter_1, s32 parameter_2);

s32 equip_start_managed_thread(s32 thread_id, EquipMenuDescriptor* desc) {
    if (g_equip_thread_state == 0) {
        if (is_event_thread_running(thread_id) != 0) {
            return 1;
        }
        g_menu_descriptor = desc;
        initialize_event_thread(thread_id, desc->entry);
        battle_store_thread_function_parameters(thread_id, (s32)g_menu_descriptor, 0, 0);
        g_equip_thread_state = 1;
        return 1;
    }
    g_equip_thread_state = is_event_thread_running(thread_id);
    return g_equip_thread_state;
}
