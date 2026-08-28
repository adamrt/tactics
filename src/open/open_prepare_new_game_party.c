#include "psx/types.h"

extern void open_load_world_overlay(s32 mode);
extern void main_new_game_set_party(s32 party_index);
extern void world_generate_formation_unit_names(void);
extern u32 g_open_runtime_flags;

/* Runtime flag bits: 0x80 world overlay loaded, 0x100 party chosen,
 * 0x4000 << party_mode selects the party (three bits, 0x1C000). */
#define OPEN_FLAG_WORLD_OVERLAY_LOADED 0x80
#define OPEN_FLAG_PARTY_CHOSEN         0x100
#define OPEN_PARTY_MODE_FLAG_BASE      0x4000
#define OPEN_PARTY_MODE_FLAG_MASK      0x1C000

void open_prepare_new_game_party(s32 party_mode, s32 world_load_mode) {
    u32 initial_flags;
    u32 flags;
    u32 party_mode_flag;
    u32 value;

    initial_flags = g_open_runtime_flags;
    if ((initial_flags & OPEN_FLAG_WORLD_OVERLAY_LOADED) == 0) {
        g_open_runtime_flags = initial_flags | OPEN_FLAG_WORLD_OVERLAY_LOADED;
        open_load_world_overlay(world_load_mode);
    }

    value = OPEN_PARTY_MODE_FLAG_BASE;
    flags = g_open_runtime_flags;
    party_mode_flag = value << party_mode;
    if ((flags & OPEN_FLAG_PARTY_CHOSEN) == 0 || (flags & party_mode_flag) == 0) {
        register u32 clear_mask __asm__("$3");

        /* ~OPEN_PARTY_MODE_FLAG_MASK. Kept as asm: unpinned, GCC gives the
         * mask $v0 and flags $v1 (target: $v1 / $a0); pinned but written in
         * C, the delay-slot filler hoists the lui into the preceding beqz
         * slot. The volatile block holds both the register and the position. */
        __asm__ volatile(
            "lui %0, 0xfffe\n\t"
            "ori %0, %0, 0x3fff"
            : "=r"(clear_mask));
        value = (flags | OPEN_FLAG_PARTY_CHOSEN) & clear_mask;
        g_open_runtime_flags = value | party_mode_flag;
        main_new_game_set_party(party_mode);
        world_generate_formation_unit_names();
    }
}
