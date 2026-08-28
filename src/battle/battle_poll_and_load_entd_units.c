#include "psx/types.h"

extern void* g_entd_set;

extern void* get_entd(void);
extern void battle_load_entd_units(void* entd_data, s32 mode);
extern void main_call_game_free(void* allocation);

s32 battle_poll_and_load_entd_units(void) {
    void* entd_data;

    entd_data = get_entd();
    if (entd_data == (void*)-1) {
        goto return_zero;
    }
    if (entd_data == 0) {
        return 1;
    }
    battle_load_entd_units(entd_data, 0);
    main_call_game_free(g_entd_set);

return_zero:
    return 0;
}
