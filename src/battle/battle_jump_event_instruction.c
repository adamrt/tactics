#include "psx/types.h"

typedef struct SVec3 {
    s16 x;
    s16 y;
    s16 z;
} SVec3;

typedef struct battle_stats {
    u8 pad[0x3b];
    u8 state;
} battle_stats_t;

typedef struct EventInstr {
    u8 pad[2];
    u8 param0;
    u8 param1;
} EventInstr;

extern s32 battle_load_halfword(void);
extern s32 func_80133158(s16);
extern SVec3* battle_get_another_coord_ptr_by_misc_id(s32);
extern void battle_increment_another_coords_by_misc_id(s32, SVec3*);
extern s32 battle_get_battle_unit_index_by_misc_id(s32);
extern battle_stats_t* battle_get_battle_stats_from_battle_id(s32);
extern void func_8008C7CC(s32, u8, s32);

void battle_jump_event_instruction(EventInstr* instr) {
    SVec3 vec;
    s32 misc_id;
    SVec3* coords;
    battle_stats_t* stats;
    u8 saved;

    misc_id = func_80133158(battle_load_halfword());
    if (misc_id != 0x7D0) {
        coords = battle_get_another_coord_ptr_by_misc_id(misc_id);
        vec.x = -coords->x;
        vec.y = -coords->y;
        vec.z = -coords->z;
        battle_increment_another_coords_by_misc_id(misc_id, &vec);
        stats = battle_get_battle_stats_from_battle_id(
            battle_get_battle_unit_index_by_misc_id(misc_id));
        saved = stats->state;
        stats->state = 6;
        func_8008C7CC(misc_id, instr->param1, instr->param0 - 1);
        stats->state = saved;
    }
}
