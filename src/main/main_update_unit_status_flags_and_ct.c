#include "fft/battle.h"
#include "psx/types.h"

extern s32 main_set_status_ct(battle_stats_t* unit, s32 status_id, s32 removing);

void main_update_unit_status_flags_and_ct(battle_stats_t* unit) {
    s32 status;
    /* Pins: without them the loop body is identical up to a permutation of
     * $v0/$v1/$a0-$a2 (register-only diff); the fences keep the second
     * innate load from being CSE'd with the first. */
    register u8* status_fields __asm__("$5");
    u32 innate;
    u32 immunity;
    register u32 current __asm__("$4");
    register u32 inflicted __asm__("$6");

    if (unit->movement_abilities[2] & 8) {
        unit->innate_status[2] |= 0x40;
    }

    status = 0;
    do {
        status_fields = (u8*)unit + status;
        __asm__ volatile("addiu %0,%0,1" : "=r"(status) : "0"(status));
        innate = status_fields[0x4e];
        __asm__("" : "=r"(innate) : "0"(innate) : "memory");
        immunity = status_fields[0x53];
        current = status_fields[0x4e];
        inflicted = status_fields[0x1bb];
        __asm__("" : "=r"(inflicted) : "0"(inflicted) : "memory");
        innate = ~innate;
        immunity &= innate;
        current |= inflicted;
        status_fields[0x53] = immunity;
        status_fields[0x58] = current;
    } while (status < 5);

    for (status = 0x18; status < 0x28; status++) {
        s32 status_byte = status / 8;
        s32 status_bit = status & 7;

        if ((unit->inflicted_status[status_byte] & (0x80 >> status_bit)) && unit->status_ct[status - 0x18] == 0) {
            main_set_status_ct(unit, status, 0);
        }
    }
}
