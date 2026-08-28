#include "psx/types.h"

extern u8* g_equip_unit_data[];
extern u8* g_equip_graphics_context;
extern void* g_equip_render_otag;
extern s32 g_event_mode;
extern s32 g_equip_input_primary_repeat;
extern s16 g_equip_message_thread_active;
extern u8 g_equip_queued_sound_effect_id;
extern u8 g_equip_suppress_queued_sound;
extern u8 g_equip_screen_state;
extern void (*g_equip_screen_state_handlers[])(void);
extern s16 g_equip_initial_equipment[];
extern u8 D_801E87DC;
extern s32 g_sound_effect_id_to_play;

extern void bcopy(const void* source, void* destination, u32 size);
extern void equip_initialize_screen(void);
extern void func_801CD7C4(s32, s32);
extern void equip_update_input_and_message_state(void);
extern void equip_start_help_text_thread(s32);
extern void battle_restore_text_pointer_table(void);
extern void equip_select_text_palette_and_metrics(s32);
extern u8* get_battle_stats_pointer(s32 unit);
extern void main_refresh_unit_stats_and_statuses(void);

s32 equip_out_entrypoint(s32 unit, void* otag) {
    s32 result;
    s32 i;
    u8 changed;
    s32 tmp;
    u8* stats;
    s16* saved;
    u8* equipment;

    if (g_equip_screen_state == 0) {
        equip_initialize_screen();
        bcopy(g_equip_unit_data[0] + 0x54, g_equip_initial_equipment, 0xA);
        g_equip_screen_state = 1;
    }
    g_equip_render_otag = otag;
    func_801CD7C4(0, -1);
    result = *(s32*)g_equip_graphics_context;
    changed = 0;
    if (g_event_mode != 0) {
        tmp = g_equip_message_thread_active == 0;
        changed = tmp;
    }
    D_801E87DC = changed;
    equip_update_input_and_message_state();
    if (g_equip_input_primary_repeat & 0x100) {
        equip_start_help_text_thread(3);
    }
    if (D_801E87DC != 0) {
        if (g_event_mode == 0) {
            battle_restore_text_pointer_table();
        }
    }
    equip_select_text_palette_and_metrics(g_event_mode);
    g_equip_screen_state_handlers[g_equip_screen_state]();
    if (g_equip_suppress_queued_sound != 0) {
        g_equip_queued_sound_effect_id = 0;
    }
    if (g_equip_queued_sound_effect_id != 0) {
        g_sound_effect_id_to_play = g_equip_queued_sound_effect_id;
    }
    g_equip_queued_sound_effect_id = 0;
    if (g_equip_screen_state != 0xFF) {
        return result;
    }
    i = 0;
    saved = g_equip_initial_equipment;
    equipment = g_equip_unit_data[0];
    for (; i < 5; i++) {
        if (*(u16*)(equipment + 0x54) != *saved) {
            break;
        }
        saved++;
        equipment += 2;
    }
    stats = get_battle_stats_pointer(unit);
    if (*(u16*)(stats + 0x2A) < *(u16*)(stats + 0x28)) {
        *(u16*)(stats + 0x28) = *(u16*)(stats + 0x2A);
    }
    if (*(u16*)(stats + 0x2E) < *(u16*)(stats + 0x2C)) {
        *(u16*)(stats + 0x2C) = *(u16*)(stats + 0x2E);
    }
    main_refresh_unit_stats_and_statuses();
    return i < 5;
}
