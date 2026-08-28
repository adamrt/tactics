#include "fft/battle.h"
#include "psx/types.h"

extern s32 rand(void);
extern void main_refresh_unit_stats_and_statuses(battle_stats_t* unit);

void main_apply_unit_level_growth(battle_stats_t* unit, s32 level_down) {
    battle_stats_t* stats;
    s32 down;
    u8* raw_stat_base;
    /* Pins: as a pseudo raw_stat is split into two biased induction pointers
     * (volatile fixes that but reshuffles every saved register). */
    register u8* raw_stat __asm__("$18");
    u8* growth;
    u32 value;
    u32 divisor;
    register u8 level __asm__("$23");
    u32 middle;
    u32 low;
    u32 high;
    u32 minimum_growth;
    register u32 quotient __asm__("$2");
    u32 stored_byte;

    stats = unit;
    __asm__("" : "=r"(stats) : "0"(stats));
    down = level_down;
    raw_stat_base = stats->raw_stats;
    raw_stat = raw_stat_base;
    growth = &stats->raw_stats[0x0f];
    level = stats->level;

    do {
        middle = raw_stat[1];
        __asm__("" : "=r"(middle) : "0"(middle) : "memory");
        divisor = *growth;
        low = raw_stat[0];
        __asm__("" : "=r"(low) : "0"(low) : "memory");
        high = raw_stat[2];
        __asm__("" : "=r"(high) : "0"(high) : "memory");
        middle <<= 8;
        low += middle;
        high <<= 16;
        value = low + high;
        minimum_growth = divisor;
        if (divisor == 0) {
            minimum_growth = 1;
        }
        divisor = minimum_growth + level;
        rand();
        if (down) {
            quotient = value / divisor;
            value -= quotient;
        } else {
            quotient = value / divisor;
            value += quotient;
        }
        growth += 2;
        if (value > 0x00ffffff) {
            value = 0x00ffffff;
        }
        stored_byte = value >> 8;
        raw_stat[1] = stored_byte;
        stored_byte = value >> 16;
        raw_stat[0] = value;
        raw_stat[2] = stored_byte;
        raw_stat += 3;
    } while ((s32)raw_stat < (s32)(raw_stat_base + 0x0f));

    main_refresh_unit_stats_and_statuses(stats);
    if (stats->hp > stats->max_hp) {
        stats->hp = stats->max_hp;
    }
    if (stats->mp > stats->max_mp) {
        stats->mp = stats->max_mp;
    }
}
