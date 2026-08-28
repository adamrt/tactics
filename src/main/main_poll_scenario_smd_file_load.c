extern int main_check_file_still_loading(void);
extern int SuzukiPutPlaySMD(void* smd_data);

/*
 * Slot zero holds the SMD load currently in flight.  Slots 1 and 2 hold the
 * resulting music handles, while slots 8 and 9 hold their source SMD data.
 */
extern int g_music_handles;

int main_poll_scenario_smd_file_load(void) {
    int* state = &g_music_handles;

    if (*state == 0) {
        return 0;
    }
    if (main_check_file_still_loading() != 0) {
        return 1;
    }
    state[g_music_handles] = SuzukiPutPlaySMD((void*)(&g_music_handles)[g_music_handles + 7]);
    *state = 0;
    return 0;
}
