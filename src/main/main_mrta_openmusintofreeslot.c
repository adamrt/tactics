typedef struct ScenarioSmdFile {
    int sector;
    int size;
} ScenarioSmdFile;

extern void* main_get_smd(int sector, int size);
extern int SuzukiPutPlaySMD(void* smd_data);

extern ScenarioSmdFile g_scenario_smd_files[];
extern void* g_loaded_smd_data[];

int main_mrta_openmusintofreeslot(int scenario) {
    int checked_slots = 0;
    int file_offset = scenario * 8;
    void** loaded_smd_base = g_loaded_smd_data;
    int* handle = (int*)((char*)loaded_smd_base - 0x1c);
    void** loaded_smd = loaded_smd_base;
    void* smd;

    do {
        if (*loaded_smd == 0) {
            smd = main_get_smd(
                *(int*)((char*)g_scenario_smd_files + file_offset),
                *(int*)((char*)g_scenario_smd_files + file_offset + 4));
            *loaded_smd = smd;
            *handle = SuzukiPutPlaySMD(smd);
            goto smd_opened;
        }
        handle++;
        checked_slots++;
        loaded_smd++;
        continue;
    smd_opened:
        return checked_slots + 1;
    } while (checked_slots < 2);
    return 0;
}
