#include "fft/data.h"
#include "psx/etc.h"

extern int g_current_event_id;
extern entd_file_t* g_entd_set;
extern u8 g_cd_file_state;

extern int main_open_entd(void);
extern entd_encounter_t* get_entd(void);
extern void open_file_to_ram_center(void* file_header);
extern void main_clear_party(void);
extern void main_initialize_unit(entd_encounter_t* entd, int unit_id, int guest_id, int initialize_for_battle);
extern void game_free_with_extra_steps(void* allocation);

void main_event_start_initialize_unit_data(int event_id) {
    entd_encounter_t* entd;
    int unit_id;

    g_current_event_id = event_id;
    while (main_open_entd() == 0) {
        VSync(0);
        open_file_to_ram_center(&g_cd_file_state);
    }

    unit_id = -1;
retry_entd:
    entd = get_entd();
    if (entd == (entd_encounter_t*)unit_id) {
        goto done;
    }
    if (entd == 0) {
        goto wait_for_entd;
    }

    main_clear_party();
    for (unit_id = 0; unit_id < 16; unit_id++) {
        main_initialize_unit(entd, unit_id, 0, 1);
    }
    game_free_with_extra_steps(g_entd_set);
    goto done;

wait_for_entd:
    VSync(0);
    open_file_to_ram_center(&g_cd_file_state);
    goto retry_entd;

done:
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
