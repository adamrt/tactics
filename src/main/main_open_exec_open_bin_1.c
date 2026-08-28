extern void* g_low_overlay_load_address;

extern void* main_get_dat_as_wd(int sector, int size, void* destination);
extern int open_bin_main(int mode);

int main_open_exec_open_bin_1(int mode) {
    main_get_dat_as_wd(0x14ff0, 0x36800, g_low_overlay_load_address);
    return open_bin_main(mode);
}
