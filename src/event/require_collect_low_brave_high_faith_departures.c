#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* get_battle_stats_pointer(s32 index);
extern battle_stats_t* find_unit_by_id(u32 unit_id, s32* battle_index);
extern void require_update_bio_variable_for_unit_class(s32 sprite_id,
    s32 variable);
extern void require_noop_801c43e0(s32 battle_index, s32 unit_id,
    s32 sprite_id);

extern u8 g_require_formation_sprite_groups[];
extern s32 g_require_affected_unit_count;
extern s32 g_require_affected_unit_message_args[];
extern u8 g_require_work[];

#define MESSAGE_ID(index)   (*(s32*)(g_require_work + 0x72c0 + ((index) << 2)))
#define BATTLE_INDEX(index) (*(s32*)(g_require_work + 0x7388 + ((index) << 2)))

/* Empty asm constraints below emit no instructions; they preserve the retail
 * compiler's register allocation and memory scheduling at branch joins. */

s32 require_collect_low_brave_high_faith_departures(void) {
    register s32 departure_count __asm__("$18") = 0;
    register s32 battle_index __asm__("$17") = 0;
    u8* sprite_groups = g_require_formation_sprite_groups;
    s32* message_args = g_require_affected_unit_message_args;

    g_require_affected_unit_count = 0;
    do {
        battle_stats_t* unit = get_battle_stats_pointer(battle_index);
        s32 found_index;
        battle_stats_t* found_unit = find_unit_by_id(unit->unit_id, &found_index);
        u32 sprite;

        if (found_index >= 0 && battle_index == found_index && found_unit->formation_index != 0xff && found_unit->unit_id != 0 && found_unit->formation_index < 0x10 && ((sprite = found_unit->character_identity) == 0 || sprite >= 4) && found_unit->unit_id >= 4) {
            s32 brave = found_unit->original_brave;
            s32 faith = found_unit->original_faith;

            if (brave < 6) {
                s32 formation_index = 0;

                if (sprite < 0x80) {
                    s32 current_sprite = sprite;
                    register u8* row_start __asm__("$5") = sprite_groups;
                    for (;;) {
                        s32 column = 0;
                        u8* row = row_start;
                        for (; column < 3; column++) {
                            if (current_sprite == *row)
                                break;
                            row++;
                        }
                        {
                            register s32 three __asm__("$2") = 3;
                            if (column != three)
                                break;
                        }
                        formation_index++;
                        if (formation_index >= 0x49)
                            break;
                        row_start += 3;
                    }
                    if (formation_index == 0x49)
                        formation_index = 0;
                    if (formation_index == 0x47)
                        formation_index = 0x48;
                    {
                        s32 count = g_require_affected_unit_count;
                        s32 offset = count << 2;
                        s32 message_id;
                        message_args[count] = current_sprite;
                        message_id = formation_index + 0x1018;
                        MESSAGE_ID(count) = message_id;
                        BATTLE_INDEX(count) = battle_index;
                        g_require_affected_unit_count = count + 1;
                    }
                    require_update_bio_variable_for_unit_class(found_unit->character_identity,
                        0xd);
                } else {
                    s32 count = g_require_affected_unit_count;
                    s32 offset = count << 2;
                    u32 generic_sprite;
                    message_args[count] = found_unit->unit_id;
                    generic_sprite = found_unit->character_identity;
                    g_require_affected_unit_count = count + 1;
                    BATTLE_INDEX(count) = battle_index;
                    MESSAGE_ID(count) = ((generic_sprite - 0x80) << 2) + (battle_index & 3) + 0x1000;
                }
                {
                    s32 noop_battle_index = battle_index;
                    __asm__("" : "=r"(noop_battle_index)
                        : "0"(noop_battle_index));
                    require_noop_801c43e0(noop_battle_index,
                        found_unit->unit_id, found_unit->character_identity);
                }
                departure_count++;
                battle_index++;
                continue;
            }

            if (faith >= 0x5f) {
                s32 formation_index = 0;

                if (sprite < 0x80) {
                    s32 current_sprite = sprite;
                    u8* row_start = sprite_groups;
                    for (;;) {
                        s32 column = 0;
                        u8* row = row_start;
                        for (; column < 3; column++) {
                            if (current_sprite == *row)
                                break;
                            row++;
                        }
                        {
                            register s32 three __asm__("$2") = 3;
                            if (column != three)
                                break;
                        }
                        formation_index++;
                        if (formation_index >= 0x49)
                            break;
                        row_start += 3;
                    }
                    if (formation_index == 0x49)
                        formation_index = 0;
                    if (formation_index == 0x47)
                        formation_index = 0x48;
                    {
                        s32 count = g_require_affected_unit_count;
                        s32 message_id;
                        s32 unit_id = found_unit->unit_id;
                        message_args[count] = unit_id;
                        message_id = formation_index + 0x1062;
                        MESSAGE_ID(count) = message_id;
                        BATTLE_INDEX(count) = battle_index;
                        g_require_affected_unit_count = count + 1;
                    }
                    require_update_bio_variable_for_unit_class(found_unit->character_identity,
                        0xe);
                    departure_count++;
                } else {
                    s32 count = g_require_affected_unit_count;
                    u32 generic_sprite;
                    message_args[count] = found_unit->unit_id;
                    generic_sprite = found_unit->character_identity;
                    g_require_affected_unit_count = count + 1;
                    BATTLE_INDEX(count) = battle_index;
                    MESSAGE_ID(count) = ((generic_sprite - 0x80) << 2) + (battle_index & 3) + 0x100c;
                    __asm__ volatile("" : "=r"(departure_count)
                        : "0"(departure_count) : "memory");
                    departure_count++;
                }
            }
        }
        battle_index++;
    } while (battle_index < 0x15);
    return departure_count;
}
#undef MESSAGE_ID
#undef BATTLE_INDEX
