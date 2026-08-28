#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* get_battle_stats_pointer(s32 unit_id);
extern u8 g_debugchr_level;
extern u8 g_debugchr_experience;
extern u8 g_debugchr_brave;
extern u8 g_debugchr_faith;
extern s16 g_debugchr_zodiac;
extern u8 g_debugchr_move;
extern u8 g_debugchr_speed;
extern u8 g_debugchr_jump;
extern s16 g_debugchr_editor_values[];
extern s16 g_debugchr_first_maximum;
extern s16 g_debugchr_second_maximum;
extern s16 g_debugchr_third_maximum;

void debugchr_apply_editor_values_to_battle_unit(s32 unit_id) {
    battle_stats_t* unit;
    register s16* editor_values __asm__("$6");
    s32 zodiac;
    u32 unit_flags;

    unit = get_battle_stats_pointer(unit_id);
    __asm__ volatile("" : "=r"(unit) : "0"(unit));
    editor_values = g_debugchr_editor_values;
    __asm__ volatile("" : "=r"(editor_values) : "0"(editor_values));

    if (g_debugchr_first_maximum < editor_values[0])
        editor_values[0] = g_debugchr_first_maximum;
    if (g_debugchr_second_maximum < editor_values[3])
        editor_values[3] = g_debugchr_second_maximum;
    if (g_debugchr_third_maximum < editor_values[6])
        editor_values[6] = g_debugchr_third_maximum;
    unit->hp = editor_values[0];
    unit->mp = editor_values[3];
    unit->ct = editor_values[6];
    unit->level = g_debugchr_level;
    unit->experience = g_debugchr_experience;
    unit->brave = g_debugchr_brave;
    unit->faith = g_debugchr_faith;
    __asm__ volatile("" : : : "memory");
    zodiac = g_debugchr_zodiac;
    /* The zodiac sign lives in the top nibble of the halfword at 0x008. */
    unit_flags = *(u16*)&unit->_pad008;
    zodiac <<= 12;
    unit_flags &= 0x0fff;
    unit_flags |= zodiac;
    *(u16*)&unit->_pad008 = unit_flags;
    unit->move = g_debugchr_move;
    unit->attributes[2] = g_debugchr_speed;
    unit->jump = g_debugchr_jump;
}
