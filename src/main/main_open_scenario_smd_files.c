typedef struct ScenarioSmdFile {
    int sector;
    int size;
} ScenarioSmdFile;

extern void* smd_malloc(int size);
extern int main_call_build_file_header(int sector, int size, void* destination);
extern void main_animation_exception_handler(int error_code);

extern ScenarioSmdFile g_scenario_smd_files[];
extern void* g_loaded_smd_data[];

int main_open_scenario_smd_files(int scenario) {
    int checked_slots = 0;
    int file_offset = scenario * 8;
    int slot = 1;
    /* The pending-slot word lives 0x20 bytes before the two raw-data slots. */
    void** loaded_smd_base = g_loaded_smd_data;
    /* Pinned: unpinned, GCC gives the la to the walking pointer and copies
     * it to the base ($s1/$s4 swapped); index forms bias the pointer by 4. */
    register void** loaded_smd __asm__("$17") = loaded_smd_base;
    void* buffer;

    do {
        checked_slots++;
        if (*loaded_smd == 0) {
            buffer = smd_malloc(
                *(int*)((char*)g_scenario_smd_files + file_offset + 4));
            if (buffer != 0) {
                if (main_call_build_file_header(
                        *(int*)((char*)g_scenario_smd_files + file_offset),
                        *(int*)((char*)g_scenario_smd_files + file_offset + 4),
                        buffer)
                    == 0) {
                    *loaded_smd = buffer;
                    *(int*)((char*)loaded_smd_base - 0x20) = slot;
                    goto smd_opened;
                }
                main_animation_exception_handler(0x11);
                return 0;
            }
            main_animation_exception_handler(0x11);
            return 0;
        smd_opened:
            return slot;
        }
        slot++;
        loaded_smd++;
    } while (checked_slots < 2);
    return 0;
}
