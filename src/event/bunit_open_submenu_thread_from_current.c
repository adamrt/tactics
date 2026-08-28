#include "psx/types.h"

typedef struct {
    void (*func)(void); /* 0x00 */
    u16 f4;             /* 0x04 */
    u16 f6;             /* 0x06 */
} BunitEventDef;

typedef struct {
    u8 pad0[0x1C];      /* 0x00 */
    u16 f1C;            /* 0x1C */
    u8 pad1[0xE];       /* 0x1E */
    u16 f2C;            /* 0x2C */
    u8 pad2[2];         /* 0x2E */
    BunitEventDef* def; /* 0x30 */
} BunitEventObj;

extern s32 g_current_event_thread_id;
extern s32 (*g_event_threads)[256];
extern u32* D_801E3C40;

extern u32* battle_get_controller_input_pointer(s32 arg0);
extern void battle_handle_menu_action(BunitEventObj* obj, s32 arg1);
extern void initialize_event_thread(s32 id, void* entry);
extern void store_thread_parameters_5(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void wait_for_event_thread(s32 id);
extern void stop_current_event_thread(void);
extern void text_character_handling_thread(void);

void bunit_open_submenu_thread_from_current(void) {
    BunitEventObj* obj;
    BunitEventDef* def;
    u32* ctl;
    u16 id;
    u16 arg;
    u16 f2C;
    u16 f1C;

    obj = (BunitEventObj*)g_event_threads[g_current_event_thread_id][0];
    obj->def->func();
    ctl = battle_get_controller_input_pointer(0);
    f1C = obj->f1C;
    def = obj->def;
    f2C = obj->f2C;
    D_801E3C40 = ctl;
    id = def->f6;
    arg = def->f4;
    *ctl = 0x20;
    battle_handle_menu_action(obj, 0);
    initialize_event_thread(id, text_character_handling_thread);
    store_thread_parameters_5(id, f2C, f1C, arg, arg);
    wait_for_event_thread(g_current_event_thread_id - 1);
    wait_for_event_thread(id);
    stop_current_event_thread();
}
